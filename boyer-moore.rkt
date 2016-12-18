#lang racket
(require racket/include)
(include "vec-tso.rkt")
;Copyright (c) Jasper 2016/12/8 Copyright Holder All Rights Reserved.

(define extract-str
  (lambda (text str)
    (letrec {[text-tail (last-idx text)]
             [str-head 0]
             [str-tail (last-idx str)]
             [last-char-str (ref-vec str-tail str)]}
      [define help
        (lambda (text-head)
          (let {[possible-head (- text-head str-tail)]}
            {cond
              [(> text-head text-tail) {list #f}]
              [(and
                 (vec-eq-var? text-head last-char-str text)
                 (eq-str? possible-head text-head str-head str-tail text str))
               {list #t possible-head}]
              [else (help (+ text-head (forward-steps (ref-vec text-head text) str)))]}))]
      (help str-tail))))

(define eq-str?
  (lambda (str1-head str1-tail str2-head str2-tail str1 str2)
    (let {[len-str1 (+ (- str1-tail str1-head) 1)]
          [len-str2 (+ (- str2-tail str2-head) 1)]}
      [define help
        (lambda (str1-head str2-head)
          {cond
            [(> str1-head str1-tail) #t]
            [(vec-eq-vec? str1-head str2-head str1 str2) (help (+ str1-head 1) (+ str2-head 1))]
            [else #f]})]
      (if (eq? len-str1 len-str2)
          (help str1-head str2-head)
          #f))))

(define forward-steps
  (lambda (var vec)
    (let {[head 0] [tail (last-idx vec)]}
      [define help
        (lambda (tail)
          {cond
            [(< tail head) (len-vec vec)]
            [(var-eq-vec? var tail vec) (- (last-idx vec) tail)]
            [else (help (- tail 1))]})]
      (help (- tail 1)))))

(define text (vector 'f 'i 'n 'd 'i 'n 'a 'h 'a 'y 's 't 'a 'c 'k 'n 'e 'e 'd 'l 'e 'i 'n 'a))
(define str (vector  'n 'e 'e 'd 'l 'e))

(extract-str text str)
