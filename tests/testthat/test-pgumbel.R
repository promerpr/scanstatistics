test_that("Updated pgumbel matches reliaR", {
  skip_if_not_installed("reliaR")
  for (i in seq_len(1000)) {
    mu <- rnorm(1, mean = 50, sd = 200)
    sigma <- exp(rnorm(1, mean = 2, sd = 4))
    q <- runif(1, min = 0, max = 1)
    expect_equal(reliaR::pgumbel(q, mu, sigma), pgumbel(q, mu, sigma))
  }
})
