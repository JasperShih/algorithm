#lang racket
(require racket/include)
(include "vec-tso.rkt")
;Copyright (c) Jasper 2016/12/18 Copyright Holder All Rights Reserved.

;70 80 31 37 10 1 48 60 33 80
;[1] 80 31 37 10 70 48 60 33 80；選出最小值1
;[1 10] 31 37 80 70 48 60 33 80；選出最小值10
;[1 10 31] 37 80 70 48 60 33 80；選出最小值31
;[1 10 31 33] 80 70 48 60 37 80 ......
;[1 10 31 33 37] 70 48 60 80 80 ......
;[1 10 31 33 37 48] 70 60 80 80 ......
;[1 10 31 33 37 48 60] 70 80 80 ......
;[1 10 31 33 37 48 60 70] 80 80 ......
;[1 10 31 33 37 48 60 70 80] 80 ......

;;vector操作總是從前面向尾端進行, 總是有head tail, 要另外的功能再另外加變數, 不要改變head tail的原始意義
;;不要先為了array迴圈多做了一次而去改變邊界條件, 如idx變成idx+1/idx-1, 這將失去了簡潔一致性,
;;要先把程式寫出來, 需要優化再優化
(define selection-sort
  (lambda (vec)
    (letrec {[tail (last-idx vec)] [first-unsorted 0] [smallest first-unsorted]}
      [define help
        (lambda (head)
          {cond
            [(>= first-unsorted tail) vec]
            [(eq? head (+ tail 1)) (swap-vec! first-unsorted smallest vec)
                                   (set! first-unsorted (+ first-unsorted 1))
                                   (set! smallest first-unsorted)
                                   (help (+ smallest 1))]
            [else {cond [(vec<vec? head smallest vec vec) (set! smallest head)]}
                  (help (+ head 1))]})]
      (help (+ smallest 1)))))


(define vec (vector 50 20))
(selection-sort vec)
