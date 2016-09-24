;; -*- lisp-interaction -*-
;;; xxdiff-style.el --- Emacs settings for editing xxdiff code.
;;;
;;; $Source: /home/blais/repos/cvsroot/conf/common/elisp/blais/xxdiff-style.el,v $
;;; $Id: xxdiff-style.el,v 1.2 2002/05/26 09:28:02 blais Exp $
;;;

;; Indentation controls
;; --------------------

(defun xxdiff-snug-close (syntax pos)
  (save-excursion
    (let (langelem)
      (if (and (eq syntax 'block-close)
               (setq langelem (assq 'block-close c-syntactic-context))
               (progn (goto-char (cdr langelem))
                      (if (eq (char-after) ?{)
                          (c-safe (forward-sexp -1)))
                      (or (looking-at "\\<do\\>[^_]")
			  (looking-at "\\<case\\>[^_]"))))
          '(before)
        '(before after)))))

(defun xxdiff-class-open (syntax pos)
  (save-excursion
    (progn (goto-char pos)
	   (if (or (looking-at "^namespace\\>")
		   (save-excursion 
		   (progn (forward-word -2)
			  (looking-at "^namespace\\>")))
		   (save-excursion 
		     (progn (forward-word -1)
			    (looking-at "^namespace\\>"))))
	       '(after)
	     '(before after)))))

(defconst xxdiff-style
  (let ((tmp-xxdiff-style

  '((c-basic-offset               . 3)                                         
    (c-hanging-braces-alist       . ((class-open        . xxdiff-class-open)        
			       	     (class-close         before)
			       	     (defun-open          before after)        
			       	     (defun-close         before after)        
			       	     (inline-open         before after)        
			       	     (inline-close        before after)        
			       	     (brace-list-open     after)               
			       	     (brace-list-close    before)              
			       	     (block-open          before after)        
			       	     (block-close       . xxdiff-snug-close)     
			       	     (substatement-open   after)               
			       	     (substatement-close  before after)        
			       	     (statement-case-open after)               
			       	     (extern-lang-open    after)               
			       	     (extern-lang-close   before after)))      
    (c-hanging-colons-alist       . ((case-label          )                    
			       	     (label               after)               
			       	     (access-label        after)               
			       	     (member-init-intro   before)              
			       	     (inher-intro         before)))            
    (c-cleanup-list               .  (empty-defun-braces
				      defun-close-semi
				      list-close-coma
				      scope-operator))
    (c-offsets-alist . ((string                . -1000)
			(c                     . c-lineup-C-comments)
			(defun-open            . 0)
			(defun-close           . 0)
			(defun-block-intro     . +)
			(class-open            . 0)
			(class-close           . 0)
			(inline-open           . 0)
			(inline-close          . 0)
			(func-decl-cont        . +)
			(knr-argdecl-intro     . +)
			(knr-argdecl           . 0)
			(topmost-intro         . 0)
			(topmost-intro-cont    . 0)
			(member-init-intro     . +)
			(member-init-cont      . 0)
			(inher-intro           . +)
			(inher-cont            . c-lineup-multi-inher)
			(block-open            . 0)
			(block-close           . 0)
			(brace-list-open       . 0)
			(brace-list-close      . 0)
			(brace-list-intro      . +)
			(brace-list-entry      . 0)
			(statement             . 0)
			(statement-cont        . +)
			(statement-block-intro . +)
			(statement-case-intro  . +)
			(statement-case-open   . +)
			(substatement          . +)
			(substatement-open     . +)
			(case-label            . +)
			(access-label          . -)
			(label                 . 0)
			(do-while-closure      . 0)
			(else-clause           . 0)
			(comment-intro         . c-lineup-comment)
			(arglist-intro         . +)
			(arglist-cont          . 0)
			(arglist-cont-nonempty . c-lineup-arglist)
			(arglist-close         . 0)
			(stream-op             . c-lineup-streamop)
			(inclass               . +)
			(cpp-macro             . -1000)
			(friend                . 0)
			(objc-method-intro     . -1000)
			(objc-method-args-cont . c-lineup-ObjC-method-args)
			(objc-method-call-cont . c-lineup-ObjC-method-call)
			(extern-lang-open      . 0)
			(extern-lang-close     . 0)
			(inextern-lang         . 0)
			(template-args-cont    . +)))) ))
      ;;; For newer versions.
    (if (not (string-match "20\.3" emacs-version))
	(setcdr
	 (assoc 'c-offsets-alist tmp-xxdiff-style)
	 (nconc (cdr (assoc 'c-offsets-alist tmp-xxdiff-style))
		'((cpp-macro-cont        . c-lineup-dont-change)
		  (namespace-open        . 0)
		  (namespace-close       . 0)
		  (innamespace           . 0)))) )
    tmp-xxdiff-style )
  "Discreet Logic Style Guide")

(require 'font-lock)
(custom-set-variables
 '(c++-font-lock-extra-types
   ;; '(c++-font-lock-keywords-2
   (append '( "Q[A-Z][a-zA-Z0-9]+" )
	   c++-font-lock-extra-types)
   ))

(c-add-style "xxdiff" xxdiff-style)

(provide 'xxdiff-style)
