<?php
define('FPDF_FONTPATH','fonts/');
require('fpdf/fpdf.php');
require_once('CellFPDF.class.inc');

class  Tax3{
	private $pdf;
	private $companyName='Name table :';
	private $taxID='start time :';
	private $cash;	
	private $buttomMargin = 10;
	private $total;
	private $item = array();
	private $cell;
	private $x;
	private $y;
	
	private $setFont = array(
		'font' => 'angsana',
		'style' => '',
		'size' => '14'
	);

	public function PageSetup(){
		$this->pdf = new FPDF('L', 'pt', 'A4');
		$this->cell = new CellFPDF($this->pdf);
		$this->pdf->SetTopMargin(0);
		$this->pdf->AddFont('angsana', '', 'angsa.php');
		$this->pdf->AddFont('angsana', 'B', 'angsab.php');
		$this->pdf->AddFont('angsana', 'I', 'angsai.php');
		$this->pdf->AddFont('angsana', 'BI', 'angsaz.php');
		$this->pdf->SetFont('angsana', '', 15);
		$this->pdf->SetDisplayMode('real', 'default');
		$this->pdf->AcceptPageBreak();
		$this->pdf->AddPage();
		$this->drawRectangle();		
		$this->addTitle();
	}
	
	private function setFontStyle($style){
		$this->setFont['style'] = $style;
		$this->pdf->SetFont($this->setFont['font'],$this->setFont['style'],$this->setFont['size']);
		$this->getFont();
		return $this;
	}
	
	private function setFontSize($size){
		$this->setFont['size'] = $size;
		$this->pdf->SetFont($this->setFont['font'],$this->setFont['style'],$this->setFont['size']);
		$this->getFont();
		return $this;
	}
	
	private function setFontFamily($family){
		$this->setFontFamily['font'] = $family;
		$this->getFont();
		return $this;
	}
	
	private function getFont(){
		$this->pdf->SetFont($this->setFont['font'],$this->setFont['style'],$this->setFont['size']);
	}
	
	
	private function setX($x,$calculate = ''){
		if($calculate == '+') $this->x += $x;
		else if($calculate == '-') $this->x -= $x; 
		else $this->x = $x;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function setY($y, $calculate = ''){
		if($calculate == '+') $this->y += $y;
		else if($calculate == '-') $this->y -= $y; 
		else $this->y = $y;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function addTitle(){
		$this->setX(20)->setY(18)->setFontSize(16)->setFontStyle("B");
		$this->cell->setWidth(15)->setHeight(20)->generateCell($this->tt("ใบแนบ"));
		$this->setX(35, '+')->setY(3)->setFontSize(37);
		$this->cell->setWidth(90)->setHeight(40)->generateCell($this->tt("ภ.ง.ด.3"));
		$this->setX(90, '+')->setY(10)->setFontSize(12);
		$this->cell->setWidth(110)->setHeight(18)->generateCell($this->tt('เลขประจำตัวประชาขน'));
		$this->setY(11, '+')->setFontStyle(null)->setFontSize(11);
		$this->cell->generateCell($this->tt('(ของผู้มีหน้าที่หักภาษี ณ ที่จ่าย)'));
		$this->setX(270, '+')->setY(11, '-');
		$this->setFontStyle('B');
		$this->cell->generateCell($this->tt('เลขประจำตัวผู้เสียภาษีอากร'));
		$this->setY(11, '+')->setFontStyle(null);
		$this->cell->generateCell($this->tt('ของผู้มีหน้าที่หักภาษี ณ ที่จ่ายที่เป็นผู้ไม่มีเลขประจำตัวประชาชน'));
	}
	
	private function drawRectangle(){
#		$this->setX(10)->setY(10);
		$this->pdf->Rect(20,50 , 810, 540);
		$this->pdf->Line(20, 115, 830, 115);
		$this->pdf->Line(20, 450, 830, 450);
#		$this->pdf->Rect(20,440,810,540);
	}
	
	private function tt($word){
		return	iconv('UTF-8', 'cp874', $word);
	}
	
	private function blocknumber($array, $count, $num){
		$countarray = 0;
		for($i = 1 ;$i<= $count ;$i++){
			if(isset($num[$i-1])) $this->pdf->cell(2, 2.5, $num[$i-1], 1,0, 'C');
			else $this->pdf->cell(2, 2.5, '', 1,0, 'C');
			if(isset($array[$countarray]) and $i == $array[$countarray]){
				$this->pdf->cell(2,2.5,'-',0,0);
				$countarray++;
			}
		}
	}
	public function save($fileOut){
		$this->pdf->Output($fileOut);
	}	
}

echo "\n test \n";

$test = new Tax3();
$test->PageSetup();
$test->save('testpdf.pdf');
?>
