<?php
class CellFPDF{
	private $fpdf = null ;
	private $height = 0;
	private $width = 0;
	private $border = 0;
	private $ln =0;
	private $align = "L";
	private $fill = 0;
	
	public function CellFPDF($fpdf){
		$this->fpdf = $fpdf;
	}
	
	public function setHeight($height){
		$this->height = $height;
		return $this;
	}
	public function setWidth($width){
		$this->width = $width;
		return $this;
	}
	public function setBorder($border){
		$this->border = $border;
		return $this;
	}
	public function setLn($ln){
		$this->setLn = $ln;
		return $this;
	}
	public function setAlign($align){
		$this->align = $align;
		return $this;
	}
	
	public function setFill($fill){
		$this->fill = $fill;
		return $this;
	}
	
	public function generateCell($word){
		$this->fpdf->cell($this->width, $this->height, $this->tt($word), $this->border, $this->ln, $this->align, $this->fill);
	}
	
	private function tt($word){
		return	iconv('UTF-8', 'cp874', $word);
	}
	
}
?>
