set exrc
set ts=4 et
ab	iN \In{\In}
ab	notE \Note{\Note}
ab	codE \Code{\Code}
ab	expL \Expl{\Expl}
set wrapmargin=8
set wrapscan
map !w :set wrapmargin=0 nowrapscan
map q :wq
map N :w:n
map z :w
map %$ :'c,.s/^/\% /
map %^ :'c,.s/^% //
map %t :%s/        /	/g
map , Ea,'
map !d :.! date
map !u :.! date -u
map !q Bi``Ea''
map !t Bi\texttt{Ea}
map !v Bi\verb@Ea@
map !c Bi\cite{Ea}
map !b bi\textbf{ea}
map !i bi\emph{ea}
map !e :s/^.*$/&&/i\end{A}-i\begin{A}a
map !r :s/^.*$/&&/A</a>-i<a href="A">+A
map !f !{fmt
map !h1 0i\section{$a}
map !h2 0i\subsection{$a}
map !h3 0i\subsubsection{$a}
ab	fiG \begin{figure}\begin{center}\end{center}% \caption{}\label{fig_f}\end{figure}
ab	bwS \begin{bwslide}\Heading{x}\end{bwslide}
ab	iT  \item 
map !! :w:!pdflatex Real.tex
