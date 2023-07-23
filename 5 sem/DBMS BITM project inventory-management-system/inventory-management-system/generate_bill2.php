<?php
require_once('vendor/tcpdf/tcpdf.php');
require_once('inc/config/constants.php');
require_once('inc/config/db.php');

// create new PDF document
$pdf = new TCPDF('P','mm',  'A4', true, 'UTF-8', false);

// set document information
$pdf->SetCreator(PDF_CREATOR);
$pdf->SetAuthor('Utkarsh');
$pdf->SetTitle('Purchase Invoice');

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

// get the purchaseID from the URL
$purchaseID = $_GET['purchaseID'];

// query the database to get the purchase details
$purchaseDetailsSql = 'SELECT * FROM purchase INNER JOIN vendor ON purchase.vendorID= vendor.vendorID WHERE purchaseID = :purchaseID';
$purchaseDetailsStatement = $conn->prepare($purchaseDetailsSql);
$purchaseDetailsStatement->execute(array(':purchaseID' => $purchaseID));
$purchaseDetails = $purchaseDetailsStatement->fetch(PDO::FETCH_ASSOC);




// calculate the total price
$uPrice = $purchaseDetails['unitPrice'];
$qty = $purchaseDetails['quantity'];
$totalPrice = $uPrice * $qty;
?>
<?php
$html = '<link href="style.css" rel="stylesheet" type="text/css">
<!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <!-- Font Awesome -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css">
    <!-- Custom Style -->
    <link rel="stylesheet" href="style.css">';

	$html .= '<h1>Purchase Invoice</h1>
	<table class="table table-bordered">
	  <thead>
		<tr>
		
		  <th scope="col">Purchase ID</th>
		  <th scope="col">Item Number</th>
		  <th scope="col">Purchase Date</th>
		  <th scope="col">Item Name</th>
		  <th scope="col">Unit Price</th>
		  <th scope="col">Quantity</th>
		  <th scope="col">Vendor Name</th>
		  <th scope="col">Vendor ID</th>
         <th scope="col">Address</th>
          
		</tr>
	  </thead>
	  <tbody>
	  <br>
		<tr style="top: margin 10px;">
		
		  <td >'. $purchaseDetails['purchaseID'] . '</td>
          <td >'. $purchaseDetails['itemNumber'] . '</td>
          <td >'. $purchaseDetails['purchaseDate'] . '</td>
          <td >'. $purchaseDetails['itemName'] . '</td>
          <td >'. $purchaseDetails['unitPrice'] . '</td>
          <td >'. $purchaseDetails['quantity'] . '</td>
          <td >'. $purchaseDetails['vendorName'] . '</td>
          <td >'. $purchaseDetails['vendorID'] . '</td>
          <td>'. $purchaseDetails['address'] .'</td>

          </tr>
          </tbody>
          </thead>
        </table>
          <h2>Total Price:RS '. number_format($totalPrice, 2) .'</h2>';
          $vendorname=$purchaseDetails['vendorName'];
    
// write the HTML content to the PDF
$pdf->writeHTML($html, true, false, true, false, '');
	
// reset pointer to the last page
$pdf->lastPage();

// Close and output PDF document
// This method has several options, check the source code documentation for more information.
$pdf->Output($vendorname.'_Purchase_Invoice.pdf', 'I');
