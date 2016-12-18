#lang racket
(require racket/include)
(include "vec-tso.rkt")
;95 27 90 49 80 58 6 9 18 50
;27 90 49 80 58 6 9 18 50 [95]；95浮出
;27 49 80 58 6 9 18 50 [90 95]；90浮出
;27 49 58 6 9 18 50 [80 90 95]；80浮出
;27 49 6 9 18 50 [58 80 90 95] ......
;27 6 9 18 49 [50 58 80 90 95] ......
;6 9 18 27 [49 50 58 80 90 95] ......
;6 9 18 [27 49 50 58 80 90 95] ......
;6 9 [18 27 49 50 58 80 90 95] ......
;6 [9 18 27 49 50 58 80 90 95] ......

;應儘量使用變數, 如head-next, 而非head+1
;cond終止條件放前面, 最外流程的中止條件放最上面, 小一層的放第二個, 再小一層的放第三個...
;以上類似函數的fixed points,
;剩下放逼近fixed points的式子.
(define bubble-sort
  (lambda (vec)
    (let {[last-unsorted (last-idx vec)]}
      [define help
        (lambda (head head-next)
          {cond
            [(<= last-unsorted 0) vec]
            [(eq? head last-unsorted) (set! last-unsorted (- last-unsorted 1))
                                      (help 0 1)]
            [else {cond [(vec>vec? head head-next vec vec) (swap-vec! head head-next vec)]}
                  (help head-next (+ head-next 1))]})]
      (help 0 1))))


(define vec (vector 27 90 49 80 58 6 9 18 95 50))
(bubble-sort vec)
