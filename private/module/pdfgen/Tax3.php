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
	
	private $personalData = array();	
	
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
		$this->addTitle();
		$this->drawRectangle();		
		$this->tableHeader();
		$this->labelTotal();
		$this->footer();
		$this->generateListGenernalTax();
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
	
	private function tt($word){
		return	iconv('UTF-8', 'cp874', $word);
	}
	
	private function blockNumber($array, $count, $num){
		$countarray = 0;
		for($i = 1 ;$i<= $count ;$i++){
			if(isset($num[$i-1])) $this->pdf->cell( 5, 7, $num[$i-1], 1,0, 'C');
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
	
	private function addTitle(){
		$this->setX(20)->setY(18)->setFontSize(16)->setFontStyle("B");
		$this->cell->setWidth(15)->setHeight(20)->generateCell("ใบแนบ");
		$this->setX(35, '+')->setY(3)->setFontSize(37);
		$this->cell->setWidth(90)->setHeight(40)->generateCell("ภ.ง.ด.3");
		$this->setX(90, '+')->setY(10)->setFontSize(12);
		$this->cell->setWidth(110)->setHeight(18)->generateCell('เลขประจำตัวประชาขน');
		$this->setY(11, '+')->setFontStyle(null)->setFontSize(11);
		$this->cell->generateCell('(ของผู้มีหน้าที่หักภาษี ณ ที่จ่าย)');
		$this->setX(270, '+')->setY(11, '-');
		$this->setFontStyle('B');
		$this->cell->generateCell('เลขประจำตัวผู้เสียภาษีอากร');
		$this->setY(11, '+')->setFontStyle(null);
		$this->cell->generateCell('ของผู้มีหน้าที่หักภาษี ณ ที่จ่ายที่เป็นผู้ไม่มีเลขประจำตัวประชาชน');
		$this->setX(350, '+')->cell->generateCell('สาขาที่');
		$this->setX(40, '-')->setY(15, '+')->setFontSize(12)->cell->generateCell('แผ่นที่           ในจำนวน          แผ่น');
	}
	
	private function drawRectangle(){
		$this->pdf->Rect(25, 53 , 810, 540);
		$this->pdf->Line(25, 116, 834, 116);
		$this->pdf->Line(25, 170, 834, 170);
		$this->pdf->Line(25, 226, 834, 226);
		$this->pdf->Line(25, 281, 834, 281);
		$this->pdf->Line(25, 337, 834, 337);
		$this->pdf->Line(25, 392, 834, 392);
		$this->pdf->Line(25, 449, 834, 449);
		
		$this->pdf->Line(59, 53, 59 , 449);
		$this->pdf->Line(408, 53, 408 , 449);
		$this->pdf->Line(710, 53, 710 , 470);
		
		$this->pdf->Line(59, 78, 408, 78);
		$this->pdf->Line(59, 97, 408, 97);
		
		$this->pdf->Line(408, 82, 710, 82);
		
		$this->pdf->Line(710, 77, 834, 77);
		
		$this->pdf->Line(230, 53, 230, 79);
		$this->pdf->Line(120, 79, 120, 96); 
		$this->pdf->Line(470, 83, 470, 450);
		$this->pdf->Line(595, 83, 595, 450); 
		$this->pdf->Line(620, 83, 620, 470); 
		$this->pdf->Line(690, 116, 690, 470); 
		$this->pdf->Line(795, 116, 795, 470); 
		$this->pdf->Line(815, 78, 815, 470);
		
		$this->pdf->Line(25, 470, 815, 470);
		
		$this->pdf->Line(490, 470, 490, 593);
		
		
	}
	
	
	private function tableHeader(){
		$this->setX(35)->setY(55)->setFontStyle('B')->cell->setWidth(20)->setHeight(20)->generateCell('ลำ');
		$this->setY(20, '+')->cell->generateCell('ดับ');
		$this->setY(20, '+')->cell->generateCell('ที่');
		$this->setX(50, '+')->setY('40', '-')->setFontSize(11)->cell->generateCell('เลขประจำตัวประชาชน (ของผู้มีเงินได้)');
		$this->setX(190, '+')->setY('4', '-')->cell->generateCell('เลขประจำตัวผู้เสียภาษีอากร');
		$this->setY(10, '+')->setX(15, '-')->setFontSize(10)->setFontStyle(null)->cell->generateCell('(ของผู้มีเงินได้ซึ่งไม่มีบัตรตรประชาชน)');
		$this->setX(190, '-') ->setY(15, '+')->setFontSize(12)->setFontStyle('B')->cell->generateCell('สาขาที่');
		$this->setX(80, '+')->cell->generateCell('ชื่อผู้มีเงินได้');
		$this->setX(45, '+')->setFontSize(10)->setFontStyle(null)->cell->generateCell('(ให้ระบุให้ชัดเจนว่าเป็น นาย นาง นางสาว หรือยศ)');
		$this->setX(100, '-')->setY(20, '+')->setFontSize(12)->setFontStyle('B')->cell->generateCell('ที่อยู่ของผู้มีเงินได้');
		$this->setX(60, '+')->setFontSize(10)->setFontStyle(null)->cell->generateCell('(ให้ระบุเป็นเลชที่ ตรอกซอย ถนน ตำบล/แขวง อำเภอ/เขต จังหวัด)');
		$this->setX(350, '+')->setY(40, '-')->setFontSize(12)->setFontStyle('B')->cell->generateCell('รายละเอียดเกี่ยวกับการจ่ายเงิน');
		$this->setX(95, '-')->setY(35, '+')->cell->generateCell('วัน เดือน ปี ที่จ่าย');
		$this->setX(90, '+')->setY(10, '-')->cell->generateCell('ประเภทเงินได้');
		$this->setX(30, '-')->setY(15, '+')->setFontSize(10)->setFontStyle(null)->cell->generateCell('(ถ้ามีมากกว่าหนึ่งประเภทให้กรอกเรียงลงไป)');
		$this->setX(125, '+')->setY(18, '-')->setFontSize(10)->setFontStyle('B')->cell->generateCell('อัตรา');
		$this->setY(10, '+')->cell->generateCell('ภาษี');
		$this->setY(10, '+')->cell->generateCell('ร้อยละ');
		$this->setX(25, '+')->setY(15, '-')->cell->generateCell('จำนวนเงินที่จ่ายแต่ละประเภท');
		$this->setX(5, '+')->setY(10, '+')->cell->generateCell('เฉพาะคนๆหนิ่งในครั่งนี้');
		$this->setX(85, '+')->setY(40, '-')->setFontSize(12)->cell->generateCell('รวมเงินภาษีที่หักและนำส่งในครั้งนี้');
		$this->setX(20, '+')->setY(30, '+')->cell->generateCell('จำนวนเงิน');
		$this->setX(85, '+')->setY(10, '-')->cell->generateCell('เงื่อน');
		$this->setX(5, '+')->setY(20, '+')->cell->generateCell('ไข');
	}
	
	private function labelTotal(){
		$this->setX(300)->setY(450)->setFontSize(14)->setFontStyle(null)->cell->generateCell('รวมยอดเงินที่ได้และภาษีที่นำส่ง (นำไปรวมกับ');
		$this->setX(175, '+')->setY(450)->setFontStyle('B')->cell->generateCell('ใบแนบ ภ.ง.ด.3');
		$this->setX(60, '+')->setFontStyle(null)->cell->generateCell('แผ่นอื่น (ถ้ามี)');
	}
	
	private function Footer(){
		$this->setX(30)->setY(470)->setFontStyle(null)->setFontSize(10)->cell->generateCell('(ให้กรอกลำดับที่ต่อเนื่องกันไปทุกแผ่นตามเงินได้แต่ละประเภท)');
		$this->setY(20, '+')->setFontSize(14)->setFontStyle('B')->cell->generateCell('หมายเหตุ');
		$note1_1 = '1    ให้ระบุว่าว่าจ่ายเป็นค่าอะไร เช่น ค่าเช่าธนาคารค่าเช่าบัญชี ค่าทนายความ ค่าวิชาชีพแพทย์ ค่าก่อ่สร้าง ส่วนลด';
		$note1_2 = 'หรือเป็นประโยชน์ใด ๆ เนื่องจากการส่งเสริมการขาย รางวัลในการประกวด การแข่งขัน การชิงโชค ค่าจ้างในการแสดงภาพยนต์ ร้องเพลง'; 
		$note1_3 = 'ดนตรี ค่าจ้างทำของ ค่าจ้างโฆษณา ค่าขนส่งสินค้า ฯลฯ';
		$note2_1 = '2    เงื่อนใขการหักภาษี ให้กรอกดังนี้';
		$note2_2 = 'หักภาษี ณ ที่จ่าย กรอก 1                ออกให้ตลอดไป กรอก 2               กรอกให้ครั้งเดียวกรอก 3'; 
		
		$this->setY(15, '+')->setFontSize(12)->setFontStyle(null)->cell->generateCell($note1_1);
		$this->pdf->Text(46, 530, $this->tt($note1_2));
		$this->pdf->Text(46, 540, $this->tt($note1_3));
		$this->pdf->Text(33, 555, $this->tt($note2_1));
		$this->pdf->Text(49, 580, $this->tt($note2_2));
		$this->setFontSize(14);
		$this->pdf->Text(580, 520, $this->tt('ลงชื่อ'));
		$this->pdf->Text(750, 520, $this->tt('ผู้จ่ายเงิน'));
		$this->pdf->Text(590, 540, $this->tt('(                                                                    )'));
		$this->pdf->Text(580, 560, $this->tt('ตำแหน่ง'));
		$this->pdf->Text(580, 585, $this->tt('ยื่นวันที่               เดือน                                พ.ศ.'));
	}
	
	
	public function inputPersonalData($data){
		$this->personalData[] = $data;
	}
	private function generateListGenernalTax(){
		$y = 130;
		$this->listTaxForm($y);
		for( $i = 1; $i <= count($this->personalData) ; $i++){
			$this->listTaxForm($y, $i-1);
			$y += 55;
		}
		
	}
	
	private function listTaxForm($y, $number){
		$this->setX(100)->setY($y);
		$this->setFontStyle('B')->cell->generateCell('ชื่อ');
		$this->setX(20, '+')->setFontStyle(null)->cell->generateCell($this->personalData[intval($number)]->getName());
		$this->setX(150, '+')->cell->generateCell('ชื่อสกุล');
		$this->setX(40, '+')->cell->generateCell($this->personalData[intval($number)]->getSurname());
		$this->setX(250, '-')->setY('20', '+')->cell->generateCell('ที่อยู่');
		$this->setX(20, '+')->cell->generateCell($this->personalData[intval($number)]->getAddress());
	}
}


class PersonalData{
	private $name;
	private $surname;
	private $address;
	private $personalNumber;
	private $taxNumber;
	private $branch;
	
	public function setName($name){
		$this->name = $name;
		return $this;
	}
	
	public function setSurname($surname){
		$this->surname = $surname;
		return $this;
	}
	
	public function setPersonalNumber($personalNumber){
		$this->personalNumber  = $personalNumber;
		return $this;
	}
	
	public function setTaxNumber($taxNumber){
		$this->taxNumber = $taxNumber;
		return $this;
	}
	
	public functoin setAddress($address){
		$this->address = $address;
		return $this;
	}
	
	public function setBranch($branch){
		$this->branch = $branch;
		return $this;
	}
	
	public function getName(){
		return $this->name;
	}
	
	public function getSurname(){
		return $this->surname;
	}
	
	public function getAddress(){
		return $this->address;
	}
	
	public function getPersonalNumber(){
		return $this->personalNumber;
	}
	
	public function getTaxNumber(){
		return $this->taxNumber;
	}
	
	public function getBranch(){
		return $this->branch;
	}
}

$test = new Tax3();
$personalData = new PersonalData();
$personalData2 = new personalData();
$personalData3 = new personalData();
$personalData4 = new personalData();
$personalData5 = new personalData();
$personalData6 = new personalData();
$personalData7 = new personalData();
$personalData8 = new personalData();
$personalData9 = new personalData();
$saveData;

$personalData->setName('kerkkhai')->setSurname('santikurkuwong')->setBranch('2234')->setTaxNumber('15357654968')->setPersonalNumber('598765751658');
$personalData2->setName('foo')->setSurname('testname')->setBranch('2')->setPersonalNumber('4886876248')->setTaxNumber('7985764235');
$personalData3->setName('init')->setSurname('testsur')->setBranch('3')->setPersonalNumber('7985462138')->setTaxNumber('1597568468');
$personalData4->setName('foo')->setSurname('testname')->setBranch('2')->setPersonalNumber('4886876248')->setTaxNumber('7985764235');
$personalData5->setName('init')->setSurname('testsur')->setBranch('3')->setPersonalNumber('7985462138')->setTaxNumber('1597568468');
$personalData6->setName('foo')->setSurname('testname')->setBranch('2')->setPersonalNumber('4886876248')->setTaxNumber('7985764235');
$personalData7->setName('init')->setSurname('testsur')->setBranch('3')->setPersonalNumber('7985462138')->setTaxNumber('1597568468');
$personalData8->setName('foo')->setSurname('testname')->setBranch('2')->setPersonalNumber('4886876248')->setTaxNumber('7985764235');
$personalData9->setName('init')->setSurname('testsur')->setBranch('3')->setPersonalNumber('7985462138')->setTaxNumber('1597568468');

$test->inputPersonalData($personalData);
$test->inputPersonalData($personalData2);
$test->inputPersonalData($personalData3);
$test->inputPersonalData($personalData4);
$test->inputPersonalData($personalData5);

$saveData = array($personalData, $personalData2, $personalData3, $personalData4, $personalData5, $personalData6, $personalData7, $personalData8, $personalData9);


foreach($saveData as $key => $item){
}
$test->PageSetup();
$test->save('testpdf.pdf');
echo "\ntest\n";
?>
