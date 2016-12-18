#lang racket
(require racket/include)
(include "vec-lib-tso.rkt")
;Copyright (c) Jasper 2016/12/8 Copyright Holder All Rights Reserved.

(define bin-search
  (lambda (head-idx tail-idx var vec)
    (let {[mid-idx (floor (/ (+ head-idx tail-idx) 2))]}
      {cond
        [(> head-idx tail-idx) '(#f)]
        [(var=vec? var mid-idx vec) (list #t mid-idx)]
        [(var>vec? var mid-idx vec) (bin-search (+ mid-idx 1) tail-idx var vec)]
        [else (bin-search head-idx (- mid-idx 1) var vec)]})))

(define vec (vector 3 24 57 57 67 68 83 90 92 95))

(bin-search 0 (last-idx vec) 92 vec)
