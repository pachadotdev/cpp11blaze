source("dev/00-bench-all.r")

# Creation, transposition, deformation of an NxN matrix ----

run_benchmark(matrix_calculation_01_r, matrix_calculation_01_arma, matrix_calculation_01_blaze, matrix_calculation_01_eigen, 2500L * 5L, "matrix-calculation-01")
gc()

# NxN normal distributed random matrix^1000 ----

run_benchmark(matrix_calculation_02_r, matrix_calculation_02_arma, matrix_calculation_02_blaze, matrix_calculation_02_eigen, 2400L * 5L, "matrix-calculation-02")
gc()

# Sorting of N random values ----

run_benchmark(matrix_calculation_03_r, matrix_calculation_03_arma, matrix_calculation_03_blaze, matrix_calculation_03_eigen, 7000000L * 5L, "matrix-calculation-03")
gc()

# NxN cross-product matrix ----

run_benchmark(matrix_calculation_04_r, matrix_calculation_04_arma, matrix_calculation_04_blaze, matrix_calculation_04_eigen, 2800L * 5L, "matrix-calculation-04")
gc()

# Linear regression over an NxN matrix ----

run_benchmark(matrix_calculation_05_r, matrix_calculation_05_arma, matrix_calculation_05_blaze, matrix_calculation_05_eigen, 3000L * 5L, "matrix-calculation-05")
gc()
