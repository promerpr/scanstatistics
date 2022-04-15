pgumbel <- function(q, location = 0, scale = 1, lower.tail = TRUE, log.p = FALSE) {
  z <- (q - location) / scale
  cdf <- exp(-exp(-z))
  
  if (!lower.tail) {
    cdf <- 1 - cdf
  }
  if (log.p) {
    return(log(cdf))
  }
  return(cdf)
}
