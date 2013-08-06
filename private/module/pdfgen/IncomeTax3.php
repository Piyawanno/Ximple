<?php
define('FPDF_FONTPATH','fonts/');
require('fpdf/fpdf.php');
require_once('CellFPDF.class.inc');

class IncomeTax{
	private $pdf;
	private $cell;
	private $x;
	private $y;
	private $blockLength;
	private $hilfenIndex = array();
	private $setFont = array(
		'font' => 'angsana',
		'style' => '',
		'size' => '14'
	);
	
	
	private $incomeTaxData;
	
	public function PageSetup(){
		$this->pdf = new FPDF('P', 'pt', 'A4');
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
		$this->generateHeadderPage();
		$this->generateFormPersonalTax();
		$this->generateInformationTax();		
		$this->generateFooter();
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
	
	
	private function setX($x){
		$this->x = $x;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function setY($y){
		$this->y = $y;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function addX($x){
		$this->x += $x;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function addY($y){
		$this->y += $y;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function subX($x){
		$this->x -= $x;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function subY($y){
		$this->y -= $y;
		$this->pdf->setXY($this->x, $this->y);
		return $this;
	}
	
	private function setBlockLength($number){
		$this->blockLength = $number;
		return $this;
	}
	
	private function setHilfenIndex($arrayNumber){
		$this->hilfenIndex = $arrayNumber;
		return $this;
	}
	
	private function generateBlockNumber($value){
		$generateBlock = new CellFPDF($this->pdf);
		$generateBlock->setWidth(10)->setHeight(14);
		for($i =  1; $i <= $this->blockLength; $i ++){
			if(in_array($i, $this->hilfenIndex)){
				$generateBlock->setBorder(0)->generateCell('-');
			}
			$generateBlock->setBorder(1)->generateCell($value[$i-1]);
		}
		$this->hilfenIndex = NULL;
	}
	
	private function tt($word){
		return	iconv('UTF-8', 'cp874', $word);
	}
	
	private function drawVerticalLine($length){
		$this->pdf->Line($this->x, $this->y, ($this->x + $length),  $this->y);
		return $this;
	}
	
	private function drawHorizontalline($length){
		$this->pdf->Line($this->x, $this->y, $this->x, ($this->y + $length));
		return $this;
	}
	
	public function save($fileOut){
		$this->pdf->Output($fileOut);
	}	
	
	public function inputIncomeTaxData($incomeTaxData){
		$this->incomeTaxData = $incomeTaxData;
	}
	
	private function generateHeadderPage(){
		$this->pdf->Image('img/LogoTaxIncome.png', 10, 30, 430, 60);
		$this->pdf->Image('img/Frame.png', 443, 30, 130, 60);
		$this->setX(140)->setY(40)->setFontSize(18)->setFontStyle('B')->cell->generateCell('แบบยื่นรายการภาษีเงินได้หัก ณ ที่จ่าย');
		$this->addX(12)->addY(18)->setFontSize(16)->cell->generateCell('ตามมาตราที่ 59 แห่งประมาลรัษฎากร');
		$this->subX(35)->addY(13)->setFontSize(12)->setFontStyle(null)->cell->generateCell('สำหรับการหักภาษี ณ ที่จ่ายตามมาตราที่ 3 เตรส และมามตารา 50 (3) (4) (5)');
		$this->subX(55)->addY(13)->cell->generateCell('กรณีจ่ายเงินได้พีงประเมินตามมาตรา 40 (5) (6) (7) (8) และการเสียภาษีตามมาตรา 48 ทวิ แห่งประมาลรัษฎากร');
		$this->addX(384)->subY(30)->setFontSize(60)->setFontStyle('B')->cell->generateCell('ภ.ง.ด.3');
	}
	
	private function generateFormPersonalTax(){
		$this->pdf->Image('img/correct.png', 405, 122, 7, 7);
		$this->setX(30)->setY(100)->setFontSize(12)->setFontStyle('B')->cell->setWidth(78)->setheight(10)->generateCell('เลขประจำตัวประชาชน');
		$this->setFontSize(10)->setFontStyle(null)->cell->generateCell('(ของผู้มีหน้าที่');
		$this->addX(80)->addY(10)->cell->generateCell('หักภาษี ณ ที่จ่าย)');
		$this->setX(30)->addY(10)->setFontSize(12)->setFontStyle('B')->cell->setWidth(92)->generateCell('เลขประจำตัวผู้เสียภาษีอากร');
		$this->setFontSize(10)->setFontStyle(null)->cell->generateCell('(ของผู้มีหน้าที่หักภาษี ณ ที่จ่าย');
		$this->addX(80)->addY(10)->cell->generateCell('ที่เป็นผู้มีไม่มีเลขประจำตัวประชาชน');
		$this->setX(30)->addY(15)->setFontSize(14)->setFontStyle('B')->cell->setWidth(115)->generateCell('ชื่อผู้มีหน้าที่ หักภาษี ณ ที่จ่าย');
		$this->setFontStyle(null)->cell->generateCell('(หน่วยงาน) :');
		$this->addY(30)->setFontStyle('B')->cell->setWidth(20)->generateCell('ที่อยู่');
		$this->setFontStyle(null)->cell->setWidth(100)->generateCell('อาคาร');
		$this->cell->setWidth(50)->generateCell('ห้องเลขที่');
		$this->cell->setWidth(50)->generateCell('ชั้นที่');
		$this->cell->generateCell('หมู่บ้าน');
		$this->addY(20)->cell->setWidth(100)->generateCell('เลขที่');
		$this->cell->setWidth(50)->generateCell('หมู่ที่');
		$this->cell->setWidth(50)->generateCell('ตรอก/ซอย');
		$this->addY(20)->cell->setWidth(150)->generateCell('ถนน');
		$this->cell->setWidth(50)->generateCell('ตำบล/แขวง');
		$this->addY(20)->cell->setWidth(180)->generateCell('อำเภอ/เขต');
		$this->cell->setWidth(50)->generateCell('จังหวัด');
		$this->addY(20)->cell->setWidth(130)->generateCell('รหัสไปรษณีย์');
		$this->cell->generateCell('เบอร์โทรศัพท์ :');
		
		$this->addX(30)->addY(40)->setFontSize(14)->setFontStyle('B')->cell->generateCell('(1) ยื่นปกติ');
		$this->addX(100)->cell->generateCell('(2) ยื่นเพิ่มเติมครั้งที่ ');
		
		$this->setX(340)->setY(100)->setFontSize(14)->setFontStyle('B')->cell->generateCell('เดือนที่จ่ายเงินได้พิ่งประเมิน');
		$this->addY(20)->setFontSize(12)->setFontStyle(null)->cell->generateCell('(ให้ทำเครื่องหมาย"     " ลงใน "     " หน้าขื่อเดือน) พ.ศ.');
		$this->addY(20)->cell->setWidth(60)->generateCell('(1) มกราคม');
		$this->cell->generateCell('(4) เมษายน');
		$this->cell->generateCell('(7) กรกฎาคม');
		$this->cell->generateCell('(10) ตุลาคม');
		$this->addY(20)->cell->generateCell('(2) กุมภาพันธ์');
		$this->cell->generateCell('(5) พฤษภาคม');
		$this->cell->generateCell('(8) สิงหาคม');
		$this->cell->generateCell('(11) พฤศจิกายน');
		$this->addY(20)->cell->generateCell('(3) มีนาคม');
		$this->cell->generateCell('(6) มิถุนายน');
		$this->cell->generateCell('(9) กันยายน');
		$this->cell->generateCell('(12) ธันวาคม');
		
		$this->addX(10)->addY(30)->cell->setWidth(100)->generateCell('ใบเสร็จเล่มที่');
		$this->cell->generateCell('เลขที่');
		$this->addY(20)->cell->generateCell('จำนวนเงิน');
		$this->cell->generateCell('บาท');
		$this->addY(30)->cell->setWidth(150)->generateCell('ลงชื่อ');
		$this->cell->generateCell('ผู้รับเงิน');
		$this->addY(20)->cell->generateCell('วันที่');
		
		$this->setX(330)->setY(100)->drawHorizontalline(230);
		$this->addY(100)->drawVerticalLine(250);
		$this->addY(80)->drawVerticalLine(-300);
		$this->setX(30)->addY(50)->drawVerticalLine(550);
		
		$this->setX(445)->setY(123)->cell->setWidth(7)->setHeight(7)->setBorder(1)->generateCell('');
		$this->setX(334)->addY(20)->cell->generateCell('');
		for ( $i = 2 ; $i <= 12 ;$i++){
			
			$this->addX(60)->cell->generateCell('');
			if(($i % 4) == 0 && $i < 12){
				$this->addY(20);
				$this->setX(334)->cell->generateCell('');
				$i++;
			}
		}
		
		$this->setX(50)->setY(295)->cell->setWidth(10)->setHeight(10)->generateCell('');
		$this->addX(100)->cell->generateCell('');
		$this->addX(100)->subY(10)->cell->setWidth(20)->setHeight(20)->generateCell('');
		$this->cell->setBorder(0)->setHeight(20);
	}
	
	private function generateInformationTax(){
		$this->pdf->Image('img/backgroundText.png', 120, 495, 280, 20);
		$this->pdf->Image('img/Frame.png', 400, 495, 100, 20);
		
		$this->setX(70)->setY(350)->setFontSize(14)->setFontStyle('B')->cell->setWidth(70)->generateCell('นำส่งภาษีตาม');
		$this->cell->setWidth(100)->generateCell('(1) มาตรา 3 เตรส');
		$this->cell->generateCell('(2) มาตรา 48 ทวิ');
		$this->cell->generateCell('(3) มาตรา 50 (3) (4) (5)');
		$this->addY(60)->setFontSize('14')->setFontStyle(null)->cell->generateCell('มีรายละเอียดการหักเป็นรายผู้มีเงินได้  ปรากฏตาม');
		$this->addY(20)->cell->generateCell('รายการที่แนบอย่างใดอย่างหนึ่ง ดังนี้');
		
		$this->addX(220)->subY(50)->setFontSize(14)->setFontStyle('B')->cell->setWidth(60)->generateCell('ใบแบบ ภ.ง.ด.3');
		$this->setFontStyle(null)->cell->setWidth(115)->generateCell('ที่แนบพร้อมมานี้:');
		$this->cell->setWidth(100)->generateCell('จำนวน');
		$this->cell->generateCell('ราย');
		$this->addY(20)->setFontStyle('B')->cell->setWidth(175)->generateCell('หรือ');
		$this->setFontStyle(null)->cell->setWidth(100)->generateCell('จำนวน');
		$this->cell->generateCell('แผ่น');
		
		$this->addY(20)->setFontSize(14)->setFontStyle('B')->cell->setWidth(95)->generateCell('สื่อบันทึกในคอมพิวเตอร์');
		$this->setFontStyle(null)->cell->setWidth(80)->generateCell('ที่แนบพร้อมมานี้:');
		$this->cell->setWidth(100)->generateCell('จำนวน');
		$this->cell->generateCell('ราย');
		$this->addY(20)->addX(175)->setFontStyle(null)->cell->setWidth(100)->generateCell('จำนวน');
		$this->cell->generateCell('แผ่น');
		$this->addY(20)->subX(175)->setFontSize(12)->cell->generateCell('ตามหนังสือแสดงความประสงค์ฯ ทะเบียนรับเลขที่                                             )');
		$this->addY(35)->subX(170)->setFontSize(14)->setFontStyle('B')->cell->setAlign('C')->setWidth(280)->generateCell('สรุปรายการนำส่ง');
		$this->cell->setWidth(100)->generateCell('จำนวนเงิน');
		$this->addY(35)->setFontSize(14)->setFontStyle('B')->cell->setAlign('L')->setWidth(280)->generateCell('1. รวมยอดเงินได้ทั้งสิ้น');
		$this->addY(18)->cell->generateCell('2. รวมยอดภาษีนำส่งทั้งสิ้น');
		$this->addY(18)->cell->generateCell('3. เงินเพิ่ม (ถ้ามี)');
		$this->addY(18)->cell->generateCell('4. รวมยอดเงินที่นำส่งทั้งสิ้น และเงินเพิ่ม (2. + 3.)');
		$this->setX(30)->addY(20)->drawVerticalLine(550);
		
		$this->setX(130)->setY(355)->cell->setBorder(1)->setWidth(10)->setHeight(10)->generateCell('');
		$this->addX(100)->cell->generateCell('');
		$this->addX(100)->cell->generateCell('');
		$this->subX(60)->addY(30)->cell->generateCell('');
		$this->addY(40)->cell->generateCell('');
		$this->cell->setBorder(0)->setHeight(20);
	}
	
	private function generateFooter(){
		$this->pdf->Image('img/Seal.png', 470, 665, 40, 40);
		$this->setX(150)->setY(630)->setFontSize(14)->setFontStyle(null)->cell->generateCell('ข้าพจ้าข้อรับรองว่า รายงานที่แจ้งใว้ข้างต้นนี้ เป็นรายงานที่ถูกต้องและครบถ้วยทุกประการ');
		$this->addX(70)->addY(30)->cell->setWidth(150)->generateCell('ลงชื่อ');
		$this->cell->generateCell('ผู้จ่ายเงิน');
		$this->addX(15)->addY(20)->cell->generateCell('(');
		$this->cell->generateCell(')');
		$this->subX(15)->addY(20)->cell->generateCell('ตำแหน่ง');
		$this->addY(20)->cell->generateCell('ยื่นวันที่                     เดือน                                            พ.ศ.');
		$this->setX(30)->addY(30)->drawVerticalLine(550);
		$this->setFontSize(12)->setFontStyle(null);
		$this->pdf->Text(450, 770, $this->tt('ก่อนกรอกรายการ  ดูคำชี้แจงด้านหลัง'));
	}
}

class Address {
	private $buildName;
	private $roomNumber;
	private $floorNumber;
	private $village;
	private $homeNumber;
	private $moo;
	private $lanes;
	private $canton;
	private $country;
	private $postNumber;
	private $telephoneNumber;
	
	public function setBuildName($buildName){
		$this->buildName -> $buildName;
		return $this;
	}
	
	public function setRoomNumber($roomNumber){
		$this->roomNumber = $roomNumber;
		return $this;
	}
	public function setFloorNumber($floorNumber){
		$this->floorNumber = $floorNumber;
		return $this;
	}
	public function setVillageName($village){
		$this->village = $village;
		return $this;
	}
	public function setHomeNumber($homeNumber);
		$this->homeNumber = $homeNumber;
		return $this;
	}
	public function setMoo($moo){
		$this->moo = $moo;
		return $thisl;
	}
	public function setLanes ($lanes){
		$this->lanes = $lanes;
		return $lanes;
	}
	public function setCanton($canton){
		$this->canton = $canton;
		return $this;
	}
	public function setCountry($country){
		$this->country = $country;
		return $this;
	}
	public function setPostNumber($postNumber){
		$this->postNumber = $postNumber;
		return $this;
	}
	public function setTelephoneNumber($telephoneNumber){
		$this->telephoneNumber = $telephoneNumber;
		return $this;
	}
	
	public function getBuildName(){
		return $this->buildName;
	}
	
	public function getRoomNumber(){
		return $this->roomNumber;
	}
	public function getFloorNumber(){
		return $this->floorNumber;
	}
	public function getVillageName(){
		return $this->village;
	}
	public function getHomeNumber();
		return $this->homeNumber;
	}
	public function getMoo($moo){
		return $this->moo;
	}
	public function getLanes (){
		return $lanes->lanes;
	}
	public function getCanton(){
		return $this->canton
	}
	public function getCountry(){
		return $this->country;
	}
	public function getPostNumber(){
		return $this->postNumber;
	}
	public function getTelephoneNumber(){
		return $this->telephoneNumber;
	}
	
}

class IncomeTaxData{
	private $name;
	private $surname;
	private $position;
	
	private $personalNumber;
	private $taxNumber;
	private $branch;
	
	private $address;
	
	private $month;
	private $year;
	private $chechMonth = array(
		'1' => false,
		'2' => false,
		'3' => false,
		'4' => false,
		'5' => false,
		'6' => false,
		'7' => false,
		'8' => false,
		'9' => false,
		'10' => false,
		'11' => false,
		'12' => false
	);
	
	private $times;
	private $hand =  array(
		'normal' => false,
		'extended' => false
	);
	
	private $submitOn = array(
		1 => false,
		2 => false,
		3 => false
	);
	
	$inTaxIsPerson;
	$inTaxIsPaper;
	$inComputerIsPerson;
	$inComputerIsPaper;
	private $sendDetail = array(
		1 => false,
		2 => false,
	);	
	
	
	public function setPersonalNumber($personalNumber){
		$this->personalNumber = $personalNumber;
		return $this;
	}
	public function setTaxNumber($taxNumber){
		$this->taxNumber = $taxNumber;
		return $this;
	}
	public function setBranch($branch){
		$this->branch = $branch;
		return $this;
	}	
	
	public function inputAddress($address){
		$this->address = $address;
		return $this;
	} 
	
}

$test = new IncomeTax();
$test->PageSetup();
$test->save('incomeTax.pdf');
echo "\ntest\n";
