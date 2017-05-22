PROJECT_DIR=$1

bison -d PROJECT_DIR/grammar/sintactF.y
flex PROJECT_DIR/grammar/lexF1.fl

gcc -IPROJECT_DIR/include sintactF.tab.c lex.yy.c ../Compilers/src/code_gen.c ../Compilers/src/fract.c ../Compilers/src/list.c ../Compilers/src/symbol_table.c ../Compilers/src/tac.c
