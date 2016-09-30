<html>
  <head>
      <title>Protospace Machine Log</title>
  </head>

  <body>

  <h2>Machine Log</h2>

  <pre>
 
 <?

    // Sparkfun uses keys rather than passwords
    $api_key = "ENTER YOUR API KEY HERE";

    // create curl resource 
    $ch = curl_init(); 

    curl_setopt_array($ch, array(
        //don't output
        CURLOPT_RETURNTRANSFER => 1,
        // URL w. device-id and function:
        CURLOPT_URL => "https://data.sparkfun.com/output/$api_key.json",
        // useragent: your cloud user
        CURLOPT_USERAGENT => "internets"
    ));


	//execute the post
	$result = curl_exec($ch);

    // close curl resource to free up system resources 
    curl_close($ch); 

    $results = json_decode( $result );

    print_r( $results );


?>

</body>

</html>