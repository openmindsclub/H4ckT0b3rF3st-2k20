<?php
session_start();
$_SESSION['token'] = md5(uniqid(rand(), true));
$token = $_SESSION['token'];
?>
<html>
  <head>
    <title>Freepik Downloader</title>
  </head>
  <body>
    <form action="" method="POST">
      <input type="hidden" name="token" value="<?= $token; ?>">
      <input type="number" minlenght="7" maxlenght="12" name="id">
      <select name="server">
        <option selected value="">Pilih Server</option>
        <option value="1">Server 1</option>
        <option value="2">Server 2</option>
      </select>
      <input type="submit" name="submit" value="Send">
    </form>
<?php
if(isset($_POST['submit'])){
  $id     = $_POST['id'];
  $server = $_POST['server'];
  if(isset($_POST['id']) && isset($_POST['server']) && isset($_POST['token'])){
    if(is_numeric($_POST['id']) && is_numeric($_POST['server'])){
      if($token == $_POST['token']){
        $print = execute($id, $server);
        echo "<pre>";
        print_r($print);
        echo "</pre>";
        
      }
      else{
        echo "<pre>{status: false, message: Invalid token}</pre>";
      }
    }
    else{
      echo "<pre>{status: false, message: Invalid id or server}</pre>";
    }
  }
  else{
    echo "<pre>{status: false, message: You must fill all form}</pre>";
  }
}
function execute($id, $server)
        {
          $fp = fopen (dirname(__FILE__) . '/localfile.tmp', 'w+');
          $url = "http://207.46.225.90:69/download/".$server."/".$id;
          $ch = curl_init();
          curl_setopt($ch, CURLOPT_URL, str_replace(" ","%20",$url));
          curl_setopt($ch, CURLOPT_TIMEOUT, 300);
          curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
          curl_setopt($ch, CURLOPT_FILE, $fp); 
          curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
          $exe = curl_exec($ch);
          curl_close($ch);
          fclose($fp);
          return $exe;
        }
?>
  </body>
</html>