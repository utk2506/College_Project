<?php
require_once('vendor/tcpdf/tcpdf.php');
require_once('inc/config/constants.php');
require_once('inc/config/db.php');

// create new PDF document
$pdf = new TCPDF('P','mm',  'A4', true, 'UTF-8', false);

// set document information
$pdf->SetCreator(PDF_CREATOR);
$pdf->SetAuthor('Utkarsh');
$pdf->SetTitle('Sale Invoice');

// remove default header/footer
// set header and footer fonts
$pdf->setHeaderFont(Array(PDF_FONT_NAME_MAIN, '', PDF_FONT_SIZE_MAIN));
$pdf->setFooterFont(Array(PDF_FONT_NAME_DATA, '', PDF_FONT_SIZE_DATA));


// set header and footer margins
$pdf->setHeaderMargin(PDF_MARGIN_HEADER);
$pdf->setFooterMargin(PDF_MARGIN_FOOTER);

// set auto page breaks
$pdf->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

// set default monospaced font
$pdf->SetDefaultMonospacedFont('courier');

// set margins
$pdf->SetMargins(PDF_MARGIN_LEFT, PDF_MARGIN_TOP, PDF_MARGIN_RIGHT);

// set auto page breaks
$pdf->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

// set image scale factor
$pdf->setImageScale('1.25');

// set font
$pdf->SetFont('times', '', 11);


// add a page
$pdf->AddPage();

// get the saleID from the URL
$saleID = $_GET['saleID'];

// query the database to get the sale details
$saleDetailsSql = 'SELECT * FROM sale INNER JOIN customer ON sale.customerID= customer.customerID  WHERE saleID = :saleID';
$saleDetailsStatement = $conn->prepare($saleDetailsSql);
$saleDetailsStatement->execute(array(':saleID' => $saleID));
$saleDetails = $saleDetailsStatement->fetch(PDO::FETCH_ASSOC);



// calculate the total price
$uPrice = $saleDetails['unitPrice'];
$qty = $saleDetails['quantity'];
$discount = $saleDetails['discount'];
$totalPrice = $uPrice * $qty * ((100 - $discount) / 100);
?>
<?php
$html = '<link href="style.css" rel="stylesheet" type="text/css">
<!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <!-- Font Awesome -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
    <!-- Custom Style -->
    <link rel="stylesheet" href="style.css">';

	$html .= '<h1>Sale Invoice</h1>
	<table class="table table-bordered">
	  <thead>
		<tr>
		
		  <th scope="col">Sale ID</th>
		  <th scope="col">Item Number</th>
		  <th scope="col">Customer ID</th>
		  <th scope="col">Customer Name</th>
		  <th scope="col">Item Name</th>
		  <th scope="col">Sale Date</th>
		  <th scope="col">Discount</th>
		  <th scope="col">Quantity</th>
		  <th scope="col">Unit Price RS </th>
		  <th scope="col">Address</th>
		</tr>
	  </thead>
	  <tbody>
	  <br>
		<tr style="top: margin 10px;">
		
		  <td >'. $saleDetails['saleID'] .'</td>
		  <td>'. $saleDetails['itemNumber'] .'</td>
		  <td>'. $saleDetails['customerID'] .'</td>
		  <td>'. $saleDetails['customerName'] .'</td>
		  <td>'. $saleDetails['itemName'] .'</td>
		  <td>'. $saleDetails['saleDate'] .'</td>
		  <td>'. $saleDetails['discount'] .'%</td>
		  <td>'. $saleDetails['quantity'] .'</td>
		  <td><span>RS </span>' . $saleDetails['unitPrice'] . '</td>

		  
		  <td>'. $saleDetails['address'] .'</td>
		</tr>
	  </tbody>
	  </thead>
	</table>
	<h2>Total Price:RS '. number_format($totalPrice, 2) .'</h2>';
	$saleDetails=$saleDetails['customerName'];
	// write the HTML content to the PDF
	$pdf->writeHTML($html, true, false, true, false, '');
	
	// reset pointer to the last page
	$pdf->lastPage();
	
	// Close and output PDF document
	// This method has several options, check the source code documentation for more information.
	$pdf->Output($saleDetails.'_Sale_Invoice.pdf', 'I');
	
