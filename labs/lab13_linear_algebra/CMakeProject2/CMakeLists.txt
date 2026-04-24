cmake_minimum_required(VERSION 3.14)

# Политика для отладочной информации в MSVC
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Автоматическое обновление субмодуля
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Update git submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Updating git submodules...")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMODULE_RESULT}, please checkout submodules manually")
        endif()
    endif()
endif()

# Поиск Gnuplot (исправлено для переносимости)
find_package(Gnuplot)

if(NOT GNUPLOT_FOUND)
    find_program(GNUPLOT_EXECUTABLE
        NAMES gnuplot.exe gnuplot
        PATHS "C:/Program Files/gnuplot/bin"
              "C:/Program Files (x86)/gnuplot/bin"
              "$ENV{ProgramFiles}/gnuplot/bin"
              "$ENV{ProgramW6432}/gnuplot/bin"
        DOC "Path to gnuplot executable"
    )
    if(GNUPLOT_EXECUTABLE)
        message(STATUS "Gnuplot found at: ${GNUPLOT_EXECUTABLE}")
        set(GNUPLOT_FOUND TRUE)
    else()
        message(WARNING "Gnuplot not found. Install from: http://www.gnuplot.info/")
    endif()
endif()

# Имя проекта
project("CMakeProject2")

# Стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Проверка существования субмодуля matplotplusplus
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/matplotplusplus/CMakeLists.txt")
    message(FATAL_ERROR 
        "matplotplusplus submodule not found!\n"
        "Please run: git submodule update --init --recursive\n"
        "Or clone with: git clone --recursive <repository-url>"
    )
endif()

# Подключение matplotplusplus
add_subdirectory(matplotplusplus)

# Исходные файлы проекта
set(SOURCES
    CMakeProject2.cpp
    CMakeProject2.h
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

# Линковка с matplotplusplus
target_link_libraries(${PROJECT_NAME} PUBLIC matplot)

# Настройка путей включения (если нужны дополнительные)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Передача пути к Gnuplot в код (если нужно в рантайме)
if(GNUPLOT_EXECUTABLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        GNUPLOT_PATH="${GNUPLOT_EXECUTABLE}"
    )
endif()

# Настройка выходной директории (опционально)
# Раскомментируйте, если хотите, чтобы exe собирался в корневую папку репозитория
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../.."
# )