#lang racket
(require racket/include)
(include "vec-tso.rkt")
;Copyright (c) Jasper 2016/12/17 Copyright Holder All Rights Reserved.

(define merge-sort
  (lambda (vec)
    (let {[new-vec (make-vector (len-vec vec))]}
      [define split-top-down
        (lambda (head tail)
          {cond
            [(>= head tail) {list head tail}]
            [else (define mid-tail (floor (/ (+ head tail) 2)))
                  (merge-bottom-up
                    (split-top-down head mid-tail)
                    (split-top-down (+ mid-tail 1) tail))]})]
      [define merge-bottom-up
        (lambda (seg1 seg2)
          (let {[head1 (car seg1)]
                [tail1 (second seg1)]
                [head2 (car seg2)]
                [tail2 (second seg2)]}
            [define help
              (lambda (head-new-vec head1 head2)
                {cond
                  [(> head1 tail1) (copy-vec! head2 tail2 vec head-new-vec new-vec)]
                  [(> head2 tail2) (copy-vec! head1 tail1 vec head-new-vec new-vec)]
                  [else {cond
                          [(vec<vec? head2 head1 vec vec)
                           (set-vec! head-new-vec (ref-vec head2 vec) new-vec)
                           (help (+ head-new-vec 1) head1 (+ head2 1))]
                          [else
                           (set-vec! head-new-vec (ref-vec head1 vec) new-vec)
                           (help (+ head-new-vec 1) (+ head1 1) head2)]}]})]
            (help head1 head1 head2)
            (copy-vec! head1 tail2 new-vec head1 vec) ;remember to do this
            {list head1 tail2}))]
      (split-top-down 0 (last-idx vec))
      new-vec)))

(merge-sort (vector 92 77 67 8 6 84 55 85 43 67))
