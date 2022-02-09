#include <string>
#include "Application.h"
#include "FffProcessor.h"
#include "communication/ArcusCommunication.h" //To connect via Arcus to the front-end.
#include "communication/CommandLine.h" //To use the command line to slice stuff.
#include "progress/Progress.h"
#include "utils/logoutput.h"
#include "utils/string.h" //For stringcasecompare.

namespace cura
{

Application::Application()
: communication(nullptr)
, current_slice(0)
{
}

Application::~Application()
{
    delete communication;
}

Application& Application::getInstance()
{
    static Application instance; //Constructs using the default constructor.
    return instance;
}


void Application::printCall() const
{
    cura::logError("Command called:\n");
    for (size_t argument_index = 0; argument_index < argc; argument_index++)
    {
        cura::logError("%s ", argv[argument_index]);
    }
    cura::logError("\n");
}
void Application::printHelp() const
{
    logAlways("\n");
    logAlways("usage:\n");
    logAlways("CuraEngine help\n");
    logAlways("\tShow this help message\n");
    logAlways("\n");
    logAlways("CuraEngine slice [-v] [-p] [-j <settings.json>] [-s <settingkey>=<value>] [-g] [-e<extruder_nr>] [-o <output.gcode>] [-l <model.stl>] [--next]\n");
    logAlways("  -v\n\tIncrease the verbose level (show log messages).\n");
    logAlways("  -p\n\tLog progress information.\n");
    logAlways("  -j\n\tLoad settings.def.json file to register all settings and their defaults.\n");
    logAlways("  -s <setting>=<value>\n\tSet a setting to a value for the last supplied object, \n\textruder train, or general settings.\n");
    logAlways("  -l <model_file>\n\tLoad an STL model. \n");
    logAlways("  -g\n\tSwitch setting focus to the current mesh group only.\n\tUsed for one-at-a-time printing.\n");
    logAlways("  -e<extruder_nr>\n\tSwitch setting focus to the extruder train with the given number.\n");
    logAlways("  --next\n\tGenerate gcode for the previously supplied mesh group and append that to \n\tthe gcode of further models for one-at-a-time printing.\n");
    logAlways("  -o <output_file>\n\tSpecify a file to which to write the generated gcode.\n");
    logAlways("\n");
    logAlways("The settings are appended to the last supplied object:\n");
    logAlways("CuraEngine slice [general settings] \n\t-g [current group settings] \n\t-e0 [extruder train 0 settings] \n\t-l obj_inheriting_from_last_extruder_train.stl [object settings] \n\t--next [next group settings]\n\t... etc.\n");
    logAlways("\n");
    logAlways("In order to load machine definitions from custom locations, you need to create the environment variable CURA_ENGINE_SEARCH_PATH, which should contain all search paths delimited by a (semi-)colon.\n");
    logAlways("\n");
}
void Application::printLicense() const
{
    logAlways("\n");
    logAlways("Cura_SteamEngine version %s\n", VERSION);
    logAlways("Copyright (C) 2021 Ultimaker\n");
    logAlways("\n");
    logAlways("This program is free software: you can redistribute it and/or modify\n");
    logAlways("it under the terms of the GNU Affero General Public License as published by\n");
    logAlways("the Free Software Foundation, either version 3 of the License, or\n");
    logAlways("(at your option) any later version.\n");
    logAlways("\n");
    logAlways("This program is distributed in the hope that it will be useful,\n");
    logAlways("but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
    logAlways("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
    logAlways("GNU Affero General Public License for more details.\n");
    logAlways("\n");
    logAlways("You should have received a copy of the GNU Affero General Public License\n");
    logAlways("along with this program.  If not, see <http://www.gnu.org/licenses/>.\n");
}

void Application::slice(){
    std::vector<std::string> arguments;
    for (size_t argument_index = 0; argument_index < argc; argument_index++){
        arguments.emplace_back(argv[argument_index]);
    }
    communication = new CommandLine(arguments); //建立了communication的实例
                                                //传递了命令行的所有参数
}

void Application::run(const size_t argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;

    Progress::init(); //初始化了一些计算用的时间

    if (stringcasecompare(argv[1], "slice") == 0){
        slice();
    }

    if (!communication){ //如果没有建立通讯则正常结束应用程序
        exit(0);
    }
    while (communication->hasSlice()){ //是否正在进行切片
                                       //检测命令行参数是否都执行终了
        communication->sliceNext();    //进行下一次切片
    }
}

} //Cura namespace.