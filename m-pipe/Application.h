#ifndef APPLICATION_H
#define APPLICATION_H

#include "utils/NoCopy.h"
#include <cstddef> //For size_t.

namespace cura
{
class Communication;
class Slice;

/*!
 * A singleton class that serves as the starting point for all slicing.
 *
 * The application provides a starting point for the slicing engine. It
 * maintains communication with other applications and uses that to schedule
 * slices.
 */
class Application : NoCopy
{
public:
    /*
     * \brief The communication currently in use.
     *
     * This may be set to ``nullptr`` during the initialisation of the program,
     * while the correct communication class has not yet been chosen because the
     * command line arguments have not yet been parsed. In general though you
     * can assume that it is safe to access this without checking whether it is
     * initialised.
     */
    Communication* communication;

    /*
     * \brief The slice that is currently ongoing.
     *
     * If no slice has started yet, this will be a nullptr.
     */
    Slice* current_slice;

    /*!
     * \brief 获得应用程序实例
     */
    static Application& getInstance(); 

    /*!
     * \brief Print to the stderr channel what the original call to the executable was.
     */
    void printCall() const;

    /*!
     * \brief 打印帮助信息
     */
    void printHelp() const;

    /*!
     * \brief Starts the application.
     *
     * It will start by parsing the command line arguments to see what it must
     * be doing.
     *
     * This function can only be called once, because it has side-effects on
     * static fields across the application.
     * \param argc The number of arguments provided to the application.
     * \param argv The arguments provided to the application.
     */
    void run(const size_t argc, char** argv);

protected:

    /*!
     * \brief 打印使用条款
     */
    void printLicense() const;

    /*!
     * \brief 开始分层切片
     */
    void slice();

private:
    size_t argc; //命令行传递的参数数量
    char** argv; //命令行传递的参数

    /*!
    * \brief 构造函数，单一对象
    */
    Application(); 

    /*!
    * \brief 析构函数，单一对象
    */
    ~Application(); 
};

} //Cura namespace.

#endif //APPLICATION_H