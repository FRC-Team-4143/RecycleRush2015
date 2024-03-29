#include "CommandListParser.h"
#include "StringUtils.h"
#include <iostream>

std::vector<CommandParseInfo> _commands;
std::regex _rxCommandList;
std::regex _rxValidName;
bool _dirty;

CommandListParser::CommandListParser()
	: _commands(), _rxCommandList(), _rxParameterList(), _rxValidName("[A-Za-z][0-9A-Za-z]*"), _dirty(true), _haveParameterListRx(false)
{
}

bool CommandListParser::AddCommand(const CommandParseInfo& cpi) {
	if (!_IsValidName(cpi.GetName()) || _IsDuplicateName(cpi.GetName())) {
		// TODO - Throw an exception?
		return false;
	}
	for (const auto& a : cpi.GetAliases()) {
		if (!_IsValidName(a) || _IsDuplicateName(a)) {
			// TODO - Throw an exception?
			return false;
		}
	}

	_commands.push_back(cpi);
	_dirty = true;
	return true;
}

bool CommandListParser::IsValid(std::string s) {
	return std::regex_match(s, _GetCommandListRx());
}

void CommandListParser::Parse(std::string commands, std::function<void(bool, Command*, float)> fAddCommand) {
	std::cout << "CommandListParser::Parse" << std::endl;

	std::vector<std::string> result;

	auto rx = _GetCommandListRx();
	std::smatch m;
	std::cout << "[DEBUG] Command list: " << commands << std::endl;
	while (std::regex_match(commands.cbegin(), commands.cend(), m, rx)) {
		bool isParallel = m.str(1).length() > 0 && m.str(1)[0] == 'P';
		auto alias = m.str(2);
		auto parameters = m.str(3);
		auto remainder = m.str(4);

		std::cout << "[DEBUG] Parallel: " << isParallel << std::endl;
		std::cout << "[DEBUG] Alias: " << alias << std::endl;
		std::cout << "[DEBUG] Parameters: " << parameters << std::endl;

		auto values = _ParseParameterList(parameters);
		std::cout << "[DEBUG] Parsed parameters" << std::endl;

		auto cpi = _GetCommandParseInfo(alias);
		std::cout << "[DEBUG] Parsed " << cpi.GetName() << std::endl;
		cpi.CreateCommand(values, [fAddCommand, isParallel](Command* c, float t) { fAddCommand(isParallel, c, t); });
		commands = remainder;
		std::cout << "[DEBUG] Command list: " << commands << std::endl;
	}
	std::cout << "[DEBUG] Done parsing commands" << std::endl;
}

std::vector<float> CommandListParser::_ParseParameterList(std::string s) {
	std::cout << "CommandListParser::_ParseParameterList" << std::endl;

	std::vector<float> result;

	auto rx = _GetParameterListRx();
	std::smatch m;
	//std::cout << "[DEBUG] Parameter list: " << s << std::endl;
	while (std::regex_match(s.cbegin(), s.cend(), m, rx)) {
		auto parameter = m.str(1);
		auto remainder = m.str(2);

		//std::cout << "[DEBUG] Parameter: " << parameter << std::endl;

		result.push_back(std::stof(parameter));
		s = remainder;
		//std::cout << "[DEBUG] Parameter list: " << s << std::endl;
	}
	//std::cout << "[DEBUG] Done parsing parameters" << std::endl;
	return result;
}

std::regex CommandListParser::_GetCommandListRx() {
	if (_dirty) {
		std::string s;
		s += R"(\s*)"; // optional whitespace
		s += _BuildModeRx(true); // Parallel vs. Sequential (optional, group 1)
		s += _BuildNameRx(true); // Command name (required, group 2)
		s += _BuildParametersRx(true); // Parameters (required, group 3)
		s += "("; // Remainder (optional, group 4)
		s += "(?:"; // open group
		s += _BuildModeRx(false); // Parallel vs. Sequential (optional)
		s += _BuildNameRx(false); // Command name (required)
		s += _BuildParametersRx(false); // Parameters (required)
		s += ")*"; // close group, zero or more instances
		s += ")"; // close capture group
		std::cout << "[DEBUG] Command List RegEx = " << s << std::endl;
		_rxCommandList.assign(s);
		_dirty = false;
	}
	return _rxCommandList;
}

std::regex CommandListParser::_GetParameterListRx() {
	//if (_rxParameterList.mark_count() == 0) {
	if (!_haveParameterListRx) {
		std::string s;
		s += R"(\s*)"; // optional whitespace
		s += "("; // open capture group
		s += "[-+]?"; // optional sign
		s += "(?:";
		s += R"(\d+(?:\.\d*)?)"; // accept formats: ##, ##., and ##.##
		s += "|";
		s += R"(\.\d+)"; // accept formats: .##
		s += ")";
		s += ")"; // close capture group
		s += R"(\s*)"; // optional whitespace

		s += "(?:"; // open group
		s += R"(,\s*)"; // comma, optional whitespace

		s += "("; // open capture group

		s += "[-+]?"; // optional sign
		s += "(?:";
		s += R"(\d+(?:\.\d*)?)"; // accept formats: ##, ##., and ##.##
		s += "|";
		s += R"(\.\d+)"; // accept formats: .##
		s += ")";
		s += R"(\s*)"; // optional whitespace

		s += "(?:"; // open group
		s += R"(,\s*)"; // comma, optional whitespace

		s += "[-+]?"; // optional sign
		s += "(?:";
		s += R"(\d+(?:\.\d*)?)"; // accept formats: ##, ##., and ##.##
		s += "|";
		s += R"(\.\d+)"; // accept formats: .##
		s += ")";
		s += R"(\s*)"; // optional whitespace

		s += ")*"; // close group, zero or more instances
		s += ")"; // close capture group
		s += ")?"; // close group, zero or one instance
		std::cout << "[DEBUG] Parameter List RegEx = " << s << std::endl;
		_rxParameterList.assign(s);
		_haveParameterListRx = true;
	}
	std::cout << "[DEBUG] Got Parameter List RegEx" << std::endl;
	return _rxParameterList;
}

std::string CommandListParser::_GetCommandName(const std::string& alias) const {
	for (const auto& cpi : _commands) {
		if (cpi.IsMatch(alias)) {
			return cpi.GetName();
		}
	}
	std::cout << "CommandListParser::_GetCommandName: Unknown command alias" << std::endl;
	throw std::exception();
	//throw std::exception("Unknown command alias.");
}

CommandParseInfo CommandListParser::_GetCommandParseInfo(const std::string& alias) const {
	for (const auto& cpi : _commands) {
		if (cpi.IsMatch(alias)) {
			return cpi;
		}
	}
	std::cout << "CommandListParser::_GetCommandParseInfo: Unknown command alias" << std::endl;
	throw std::exception();
	//throw std::exception("Unknown command alias.");
}

std::string CommandListParser::_BuildModeRx(bool capturing) const {
	std::string s;
	s += "(?:"; // open group
	s += capturing ? "(" : "(?:";
	s += "P|Parallel|S|Sequential";
	s += ")";
	s += R"(\s*:\s*)"; // optional whitespace, colon, optional whitespace
	s += ")?"; // close group, zero or one instance
	return s;
}

std::string CommandListParser::_BuildNameRx(bool capturing) const {
	std::vector<std::string> names;
	for (auto cpi : _commands) {
		names.push_back(cpi.GetName());
		for (auto s : cpi.GetAliases()) {
			names.push_back(s);
		}
	}

	std::string s;
	s += capturing ? "(" : "(?:"; // open group
	s += Join(names, "|"); // pipe-delimited names
	s += R"()\s*)"; // close group, optional whitespace
	return s;
}

std::string CommandListParser::_BuildParametersRx(bool capturing) const {
	std::string s;
	s += R"(\(\s*)"; // open paren, optional whitespace

	s += capturing ? "(" : "";

	s += "[-+]?"; // optional sign
	s += "(?:";
	s += R"(\d+(?:\.\d*)?)"; // accept formats: ##, ##., and ##.##
	s += "|";
	s += R"(\.\d+)"; // accept formats: .##
	s += ")";
	s += R"(\s*)"; // optional whitespace

	s += "(?:"; // open group
	s += R"(,\s*)"; // comma, optional whitespace

	s += "[-+]?"; // optional sign
	s += "(?:";
	s += R"(\d+(?:\.\d*)?)"; // accept formats: ##, ##., and ##.##
	s += "|";
	s += R"(\.\d+)"; // accept formats: .##
	s += ")";
	s += R"(\s*)"; // optional whitespace

	s += ")*"; // close group, zero or more instances

	s += capturing ? ")" : "";

	s += R"(\)\s*)"; // close paren, optional whitespace
	return s;
}

bool CommandListParser::_IsDuplicateName(const std::string& s) {
	for (const auto& c : _commands) {
		if (c.GetName() == s) {
			return true;
		}
		for (const auto& a : c.GetAliases()) {
			if (a == s) {
				return true;
			}
		}
	}
	return false;
}

bool CommandListParser::_IsValidName(const std::string& s) {
	return std::regex_match(s, _rxValidName);
}
