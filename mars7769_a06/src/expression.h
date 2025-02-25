/*
--------------------------------------------------
Project: a6q3
File:    expression.h
Author:  Michael Marsillo
Version: 2025-01-16
--------------------------------------------------
*/

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "common.h"
#include "queue.h"

QUEUE infix_to_postfix(char *infixstr);

int evaluate_postfix(QUEUE queue);

int evaluate_infix(char *infixstr);

#endif
