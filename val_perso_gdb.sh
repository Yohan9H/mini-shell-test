#!/bin/bash

dir=$(pwd)

valgrind --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes --show-leak-kinds=all --vgdb=full --vgdb-error=0 --suppressions=$dir/readline.supp ./minishell

