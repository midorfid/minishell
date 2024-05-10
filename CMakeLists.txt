cmake_minimum_required(VERSION 3.22.1)

project(minishell)

set(MAIN_SRC src/main.c)

set(UTIL_SRC
    src/error.c
    src/signals.c
    src/utils.c
    src/cmd_builtins/ft_cd.c
    src/cmd_builtins/ft_echo.c
    src/cmd_builtins/ft_env.c
    src/cmd_builtins/ft_exit.c
    src/cmd_builtins/ft_export.c
    src/cmd_builtins/ft_pwd.c
    src/cmd_builtins/ft_unset.c
    src/environment/environ.c
    src/environment/ft_getenv.c
    src/environment/ft_setenv.c
    src/environment/ft_unsetenv.c
    src/execute/execute.c
    src/execute/multi_cmd.c
    src/execute/single_cmd.c
    src/execute/wait_children.c
    src/parsing/check_spec_char.c
    src/parsing/parse.c
    src/parsing/tokenize.c
    src/redirections/redir_stdin.c
    src/redirections/redir_stdout.c
    )

set(EXEC_NAME minishell)

# compiler settings
set(CMAKE_FLAGS "-Wall -Werror -Wextra")
set(CMAKE_FLAGS_DEBUG "-g -fsanitize=address -DBUILD_DEBUG")

# add library
add_subdirectory(Libft)


# - - - - - --  - --  - - - - - BUILD - - - - - - -- - - - - - -- - #

# create executable from src
add_executable(${EXEC_NAME} ${MAIN_SRC} ${UTIL_SRC})

# add includes to executable
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add libs to executable
target_link_libraries(${EXEC_NAME} readline termcap ft)
