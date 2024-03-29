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

COUNTER		:= 0 1 2 3 4 5 6 7 8 9 10 # 11 12 13 14 15 16 17 18 19 20		\
#			   21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40	\
#			   41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60	\
#			   61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80	\
#			   81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99

BOOST		:=  --boost


compile:
		@ $(COMPILER) $(CFLAG_DEBUG) $(CFLAG_WARN) $(SRCS) -o $(NAME)

table:
		@ clear
		@ printf " ______ ______ _________ ________ ________ ________ ____________ _____________ \n"
		@ printf "| Test | Time | Threads |  Goal  | Result | Weight | Iterations | Result Time |\n"
		@ printf "|------+------+---------+--------+--------+--------+------------+-------------|\n"

test_5:		compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex05.txt 2 1 ;		\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex05 \n\n"

test_20:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex20_878.txt 2 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex20 \n\n"

test_50:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex50_2.txt 3 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex50 \n\n"

test_100:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex100_1.txt 4 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex100 \n\n"

test_200:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex200_1.txt 5 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex200 \n\n"

test_500:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex500_1.txt 5 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex500 \n\n"

test_1000:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex1000_1.txt 5 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex1000 \n\n"

test_2000:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex2000_1.txt 6 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex2000 \n\n"

test_5000:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do									\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex5000_1.txt 7 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex5000 \n\n"

test_10000:	compile | $(PATH_TEST) table
		@ for number in $(COUNTER); do										\
			./$(NAME) $(BOOST) $$number $(PATH_TEST)/ex10000_1.txt 10 1 ;	\
		done ;
		@ printf " ‾‾‾‾‾‾ ‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾ ‾‾‾‾‾‾‾‾‾‾‾‾‾ \n"		
		@ printf "\n>>>> ex10000 \n\n"

$(PATH_TEST):
		@ unzip knap_tests.zip -d knap_tests

clean:
		@ rm -rf $(NAME) $(PATH_TEST) results.txt
