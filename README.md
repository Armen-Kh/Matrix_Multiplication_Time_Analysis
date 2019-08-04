#time analysis of the matrix multiplication
A*B vs A*(T)B

$ make: 
  Run makefile to generate matrix_generator.out and main.out executable files in Bin folder(make).

$ make generate: 
  Running matrix_generator.out(make generate) it's suggested generate two square matrix files(in Data folder) with user defined parameters(matris dimension). The matrices in file consist of random generated integer elements from the interval [-99, 99]. (to compare and to get a more obvious difference, it would be better to generate the first matrix, for example, with 50 rows and columns, and the second(last one) with, for example, 2000 rows and columns.

$ make run: 
  After square matrix files generation, run main.out(make run) to implement matrix multipliction with two versions of code: standart multiplication and transpose multiplication. As a result it's generated timeAnalysis.txt(Data folder) file were represented the implementation CPU time difference.

$ make gprof: 
  Note: We make compilation and linking with -pg flags, which give as oportunity to see proper time analysis for each code unit. Just running gprof tool(make gprof) we generate gprof_analysis.txt file (in Data folder) which includes full statistic information about code units effectivity.

And as a conclusion we see that with big datas matrix transpose multiplication much more effective.

