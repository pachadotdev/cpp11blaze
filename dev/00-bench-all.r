if (!require("devtools")) install.packages("devtools")
if (!require("bench")) install.packages("bench")
if (!require("armadillobenchmark")) devtools::install("dev/armadillobenchmark")
if (!require("basebenchmark")) devtools::install("dev/basebenchmark")
if (!require("blazebenchmark")) devtools::install("dev/blazebenchmark")
if (!require("eigenbenchmark")) devtools::install("dev/eigenbenchmark")

library(armadillobenchmark)
library(basebenchmark)
library(blazebenchmark)
library(eigenbenchmark)
library(bench)

run_benchmark <- function(FUN1, FUN2, FUN3, FUN4, n, name) {
  message(n)

  fout <- paste0("benchmarks/benchmarks-", name, "-", n, ".rds")

  if (!file.exists(fout)) {
    out <- mark(
      FUN1(n),
      FUN2(n),
      FUN3(n),
      FUN4(n),
      min_iterations = 10L,
      max_iterations = 10L
    )
    print(out)
    saveRDS(out, fout)
  }
}
