% — TestXeTeX_SetAngsana.tex——-
% — Chakkree Tiyawongsuwan —-
%
% อ้างอิง http://markmail.org/message/ulp3lmxfg5biv7b5
%
% Modified by Kittipong Piyawanno

\documentclass[16pt,a4paper, oneside]{article}
\usepackage{fontspec}
\usepackage{xunicode}
\usepackage{xltxtra}
\usepackage{graphicx}
\usepackage{wallpaper}
\usepackage{ulem}

\XeTeXlinebreaklocale “th_TH”
\defaultfontfeatures{Scale=1.75}
\renewcommand{\baselinestretch}{2.0}
\setmainfont{TH SarabunPSK:script=thai}
\setmainfont[BoldFont={TH SarabunPSK Bold:script=thai},
	ItalicFont={TH SarabunPSK Italic:script=thai},
	BoldItalicFont={TH SarabunPSK Bold Italic:script=thai}
]{TH SarabunPSK:script=thai}
\setsansfont{TH SarabunPSK:script=thai}
\setmonofont[Scale=0.8]{Tahoma:script=thai}

\setlength{\oddsidemargin}{0.1cm}
\setlength{\evensidemargin}{-0.6cm}
\setlength{\textwidth}{17cm}
\setlength{\textheight}{23.5cm}
\setlength{\topmargin}{-0.9cm}
\setlength{\headheight}{0.6cm}
\setlength{\headsep}{1cm}
\setlength{\parskip}{2mm}
\setlength{\parindent}{18mm}
\thispagestyle{empty}

\begin{document}
	\vskip 0.8mm
	
	\ThisCenterWallPaper{1.0}{<?=MODULE_PATH.'docgen/theme/GarudaBG.png'?>}
	\begin{center}
		\begin{huge}
			\textbf{บันทึกข้อความ}
		\end{huge}	
	\end{center}
	\vskip 0.3mm
	\begin{large}
		\textbf{ส่วนราชการ}
	\end{large}
	<?=$place?>
	\newline
	\begin{large}
		\textbf{ที่}
		<?=$document_id?>
		\hspace{\stretch{6}}
		\textbf{วันที่}
		\hspace{\stretch{2}}
	\end{large}
	<?=$write_date?>
	\hspace{\stretch{6}}
	\newline
	\begin{large}
		\textbf{เรื่อง}
	\end{large}
	<?=$topic?>
	\newline
	<?=$prefix?> <?=$receiver?>
	
	
	<?=$content?>
	
	
	\hspace{\stretch{1}}
	<?=$writer_rank?>
	\hspace{\stretch{1}}
	
	
	\hspace{\stretch{6}}
	<?=$writer_position?>
	\hspace{\stretch{3}}
\end{document}
