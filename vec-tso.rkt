;Copyright (c) Jasper 2016/12/8 Copyright Holder All Rights Reserved.

;命名時重要要表達的意思，最主要的意思要放前面，輔助說明的放後面
;function的args排序也是一樣

;對vector的操作應視為，兩個數字的操作。
;(last-idx (vector)) > -1

;vec > head-idx tail-idx
;(vector) > 0 -1
;(vector 10) > 0 0
;(vector 10 9) > 0 1
;(vector 10 9 11) > 0 2
;...


(define set-vec!
  (lambda (idx val vec)
    (vector-set! vec idx val)))

(define ref-vec
  (lambda (idx vec)
    (vector-ref vec idx)))

(define len-vec vector-length)

(define copy-vec!
  (lambda (head-ref tail-ref vec-ref head vec)
    (vector-copy! vec head vec-ref head-ref (+ tail-ref 1))))

(define swap-vec!
  (lambda (idx-1 idx-2 vec)
    (let {[tmp (vector-ref vec idx-1)]}
      (vector-set! vec idx-1 (vector-ref vec idx-2))
      (vector-set! vec idx-2 tmp))))

;if vec is empty vector, it return -1
(define last-idx
  (lambda (vec)
    (- (vector-length vec) 1)))

(define gen-vec-vec
  (lambda (pred)
    (lambda (idx1 idx2 vec1 vec2)
      (pred (ref-vec idx1 vec1) (ref-vec idx2 vec2)))))
(define vec>vec? (gen-vec-vec >))
(define vec<vec? (gen-vec-vec <))
(define vec=vec? (gen-vec-vec =))
(define vec<=vec? (gen-vec-vec <=))
(define vec>=vec? (gen-vec-vec >=))
(define vec-eq-vec? (gen-vec-vec eq?))

(define gen-var-vec
  (lambda (pred)
    (lambda (var idx vec)
      (pred var (ref-vec idx vec)))))
(define var<vec? (gen-var-vec <))
(define var>vec? (gen-var-vec >))
(define var=vec? (gen-var-vec =))
(define var<=vec? (gen-var-vec <=))
(define var>=vec? (gen-var-vec >=))
(define var-eq-vec? (gen-var-vec eq?))

(define gen-vec-var
  (lambda (pred)
    (lambda (idx var vec)
      (pred (ref-vec idx vec) var))))
(define vec<var? (gen-vec-var <))
(define vec>var? (gen-vec-var >))
(define vec=var? (gen-vec-var =))
(define vec<=var? (gen-vec-var <=))
(define vec>=var? (gen-vec-var <=))
(define vec-eq-var? (gen-vec-var eq?))
