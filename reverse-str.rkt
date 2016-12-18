#lang racket
(require racket/include)
(include "vec-lib-tso.rkt")
;Copyright (c) Jasper 2016/12/8 Copyright Holder All Rights Reserved.

;反轉字串(把"abcde"變成"edcba")
(define reverse_str
  (lambda (vec head-idx tail-idx)
    {cond
      [(>= head-idx tail-idx) vec]
      [else (swap-vec! head-idx tail-idx vec)
            (reverse_str vec (+ head-idx 1) (- tail-idx 1))]}))


(define vec (vector 'a 'b 'c 'd 'e))
(reverse_str vec 0 (last-idx vec))
