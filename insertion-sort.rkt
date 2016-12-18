#lang racket
(require racket/include)
(include "vec-tso.rkt")
;Copyright (c) Jasper 2016/12/19 Copyright Holder All Rights Reserved.

;92 77 67 8 6 84 55 85 43 67
;[92] 77 67 8 6 84 55 85 43 67
;[77 92] 67 8 6 84 55 85 43 67；將77插入92前
;[67 77 92] 8 6 84 55 85 43 67；將67插入77前
;[8 67 77 92] 6 84 55 85 43 67；將8插入67前
;[6 8 67 77 92] 84 55 85 43 67；將6插入8前
;[6 8 67 77 84 92] 55 85 43 67；將84插入92前
;[6 8 55 67 77 84 92] 85 43 67；將55插入67前
;[6 8 55 67 77 84 85 92] 43 67 ......
;[6 8 43 55 67 77 84 85 92] 67 ......

(define insertion-srot
  (lambda (vec)
    (let {[tail (last-idx vec)] [first-unsorted 0]}
      [define help
        (lambda ()
          {cond
            [(eq? first-unsorted (+ tail 1)) vec]
            [else (insert first-unsorted vec)
                  (set! first-unsorted (+ first-unsorted 1))
                  (help)]})]
      (help))))

(define insert
  (lambda (first-unsorted vec)
    [define help
      (lambda (head)
        {cond
          [(or
             (zero? first-unsorted)
             (eq? head (+ first-unsorted 1))) vec]
          [else {cond [(vec<vec? first-unsorted head vec vec) (swap-vec! first-unsorted head vec)]}
                (help (+ head 1))]})]
    (help 0)))

(define vec (vector 70 80 31 37 10 80 48 60 33 1))
(insertion-srot vec)
