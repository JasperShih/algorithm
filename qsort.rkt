#lang racket
(require racket/include)
(include "vec-lib-tso.rkt")
;Copyright (c) Jasper 2016/12/3 10:08:55 Copyright Holder All Rights Reserved.

;qsort
;選pivot [0], 設兩個index left[1] right[-1], left開始往右搜尋, 找到比pivot大的數就停住,
;right開始往左搜尋, 找到比pivot小的點就和left互換content, left+=1, right繼續往左搜尋, left和right交會時,
;pivot和left互換content, 結束一個pass, pivot兩邊再分別遞迴繼續排序.


;pivot<=big
;more-then
;find-increase
;pivot<left
(define vec-qsort
  (lambda (pivot-idx last-idx vec)
    (let {[vec-length (+ (- last-idx pivot-idx) 1)]};;need to add 1
      {cond
        [(<= vec-length 1) vec]
        [else (let {[left-idx (+ pivot-idx 1)] [right-idx last-idx]}
                ;(- left-idx 1) is posotion for pivot
                [define find-larger
                  (lambda (left-idx)
                    {cond
                      [(or
                         (= left-idx (+ last-idx 1))
                         (>vec? left-idx pivot-idx vec))
                       left-idx]
                      [else (find-larger (+ left-idx 1))]})]

                [define find-smaller
                  (lambda (right-idx)
                    {cond
                      [(or
                         (= right-idx pivot-idx)
                         (>vec? pivot-idx right-idx vec))
                       right-idx]
                      [else (find-smaller (- right-idx 1))]})]

                [define sort-logic
                  (lambda ()
                    (let {}
                      (set! left-idx (find-larger left-idx))
                      (set! right-idx (find-smaller right-idx))
                      {cond
                        [(> left-idx right-idx) (swap-vec! pivot-idx (- left-idx 1) vec)
                                                (vec-qsort pivot-idx (- left-idx 2) vec)
                                                (vec-qsort left-idx last-idx vec)]
                        [else (swap-vec! left-idx right-idx vec)
                              (sort-logic)]}))]
                (sort-logic))]})))



(define vec (vector 10 9 1 2 5 3 8 7 12 11))

(vec-qsort 0 (- (vector-length vec) 1) vec)
