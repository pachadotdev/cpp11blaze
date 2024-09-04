source("dev/00-setup.r")

# FFT over N random values ----

run_benchmark(matrix_functions_01_r, matrix_functions_01_arma, matrix_functions_01_blaze, matrix_functions_01_eigen, 2400000L, "matrix-functions-01")
gc()

# Eigenvalues of an NxX random matrix ----

run_benchmark(matrix_functions_02_r, matrix_functions_02_arma, matrix_functions_02_blaze, matrix_functions_02_eigen, 640L, "matrix-functions-02")
gc()

# Determinant of an NxN random matrix ----

run_benchmark(matrix_functions_03_r, matrix_functions_03_arma, matrix_functions_03_blaze, matrix_functions_03_eigen, 2500L, "matrix-functions-03")
gc()

# Cholesky decomposition of an NxN matrix ----

run_benchmark(matrix_functions_04_r, matrix_functions_04_arma, matrix_functions_04_blaze, matrix_functions_04_eigen, 3000L, "matrix-functions-04")
gc()

# Inverse of an NxN random matrix ----

run_benchmark(matrix_functions_05_r, matrix_functions_05_arma, matrix_functions_05_blaze, matrix_functions_05_eigen, 1600L, "matrix-functions-05")
gc()
