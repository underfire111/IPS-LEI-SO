NAME		:= prog

PATH_SRCS	:= srcs
PATH_TEST	:= knap_tests

SRCS		:= $(shell find $(PATH_SRCS) -name '*.c')

COMPILER	:= gcc
CFLAG_DEBUG	:= -g
CFLAG_WARN	:= -Wall -Wextra -Werror
CFLAG_NWARN	:= -Wno-incompatible-pointer-types		\
			   -Wno-int-conversion					\
			   -Wno-implicit-function-declaration	\

COUNTER		:= 0 1 2 3 4 5 6 7 8 9 
BOOST		:= 

compile:
		@ $(COMPILER) $(CFLAG_DEBUG) $(CFLAG_WARN) $(SRCS) -o $(NAME)

test_5:		compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex05.txt 2 1 ;		\
		done ;
		@ printf "\n>>>> ex05 \n\n"

test_8:		compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex08.txt 2 1 ;		\
		done ;
		@ printf "\n>>>> ex08 \n\n"

test_20:	compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex20_878.txt 3 1 ;	\
		done ;
		@ printf "\n>>>> ex20 \n\n"

test_40:	compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex40.txt 5 2 ;	\
		done ;
		@ printf "\n>>>> ex40 \n\n"

test_50:	compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex50_1.txt 1 2 ;	\
		done ;
		@ printf "\n>>>> ex50 \n\n"

test_100:	compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex100_1.txt 7 2 ;	\
		done ;
		@ printf "\n>>>> ex100 \n\n"

test_200:	compile | $(TEST_PATH)
		@ printf "| Test | Time | Threads |  Goal  | Result | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+------------+-------------|\n"
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex200_1.txt 10 2 ;	\
		done ;
		@ printf "\n>>>> ex200 \n\n"

$(PATH_TEST):
		@ unzip knap_tests.zip -d knap_tests

clean:
		@ rm -rf $(NAME) $(PATH_TEST)
