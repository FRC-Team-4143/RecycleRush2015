#pragma once
#include <string>
#include <vector>
#include <functional>
#include <Commands/Command.h>

class CommandParseInfo
{
public:
	CommandParseInfo(std::string name, std::vector<std::string> aliases = std::vector<std::string>(), std::function<void(std::vector<float>, std::function<void(Command*, float)>)> createCommand = nullptr);
	~CommandParseInfo();

	CommandParseInfo(const CommandParseInfo& o);

	std::string GetName() const;
	std::vector<std::string> GetAliases() const;

	bool IsMatch(std::string) const;

	void CreateCommand(std::vector<float> parameters, std::function<void(Command*, float)> addCommand) const;

private:
	std::string _name;
	std::vector<std::string> _aliases;
	std::function<void(std::vector<float>, std::function<void(Command*, float)>)> _createCommand;

	CommandParseInfo& operator =(const CommandParseInfo& o); // Not implemented
};

