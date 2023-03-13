## ---- include = FALSE---------------------------------------------------------
knitr::opts_chunk$set(
  collapse = TRUE,
  comment = "#>"
)

## ----setup--------------------------------------------------------------------
library(sparvaride)

## ----examples-----------------------------------------------------------------
delta1 <-
  matrix(c(1, 0, 0,
           0, 1, 0,
           0, 0, 1,
           1, 1, 1,
           1, 0, 1,
           1, 0, 1,
           1, 0, 1),
         nrow = 7, ncol = 3,
         byrow = TRUE)
delta2 <-
  matrix(c(1, 0, 0,
           0, 1, 0,
           0, 0, 1,
           1, 1, 1,
           1, 0, 1,
           1, 1, 1,
           1, 0, 1),
         nrow = 7, ncol = 3,
         byrow = TRUE)

## ----counting_rule_holds------------------------------------------------------
counting_rule_holds(delta1)
counting_rule_holds(delta2)

## ----citation-----------------------------------------------------------------
citation("sparvaride")

