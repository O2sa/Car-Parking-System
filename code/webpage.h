const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<title>Smart Parking System</title>
<style>
  /* Style the tab */
  .tab {
    overflow: hidden;
    border: 1px solid #ccc;
    /* background-color: #f1f1f1; */
    background-color: #f2f2f5;
    position: fixed;
    top: 74px;
    left: -1px;
    color: white;
    width: 100%;
    z-index: 2;
  }

  /* Style the buttons inside the tab */
  .tab button {
    background-color: inherit;
    float: left;
    border: none;
    outline: none;
    cursor: pointer;
    padding: 14px 16px;
    transition: 0.3s;
    font-size: 17px;
  }

  /* Change background color of buttons on hover */
  .tab button:hover {
    background-color: #ddd;
  }

  /* Create an active/current tablink class */
  .tab button.active {
    background-color: #ccc;
  }

  /* Style the tab content */
  .tabcontent {
    display: none;
    /* margin-top: 82; */
    position: absolute;
    width: 98%;
    top: 22%;
    /* left: 31%; */
    text-align: center;
  }

  table {
    position: relative;
    width: 50%;
    margin: auto;
    border-spacing: 0px;
  }

  tr {
    border: 1px solid white;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
  }

  th {
    height: 20px;
    padding: 3px 15px;
    background-color: #343a40;
    color: #FFFFFF !important;
  }

  td {
    height: 20px;
    padding: 3px 15px;
  }

  .tabledata {
    font-size: 24px;
    position: relative;
    padding-left: 5px;
    padding-top: 5px;
    height: 25px;
    border-radius: 5px;
    color: #FFFFFF;
    line-height: 20px;
    transition: all 200ms ease-in-out;
    background-color: #00AA00;
  }

  .fanrpmslider {
    width: 30%;
    height: 55px;
    outline: none;
    height: 25px;
  }

  .bodytext {
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 24px;
    text-align: left;
    font-weight: light;
    border-radius: 5px;
    display: inline;
  }

  .navbar {
    width: 100%;
    height: 50px;
    margin: 0;
    padding: 10px 0px;
    background-color: #FFF;
    color: #000000;
    border-bottom: 5px solid #293578;
  }

  .fixed-top {
    position: fixed;
    top: 0;
    right: 0;
    left: 0;
    z-index: 1030;
  }

  .navtitle {
    float: left;
    height: 50px;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 50px;
    font-weight: bold;
    line-height: 50px;
    padding-left: 20px;
  }

  .navheading {
    position: fixed;
    left: 60%;
    height: 50px;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
    font-weight: bold;
    line-height: 20px;
    padding-right: 20px;
  }

  .navdata {
    justify-content: flex-end;
    position: fixed;
    left: 70%;
    height: 50px;
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
    font-weight: bold;
    line-height: 20px;
    padding-right: 20px;
  }

  .category {
    font-family: "Verdana", "Arial", sans-serif;
    font-weight: bold;
    font-size: 32px;
    line-height: 50px;
    padding: 20px 10px 0px 10px;
    color: #000000;
  }

  .heading {
    font-family: "Verdana", "Arial", sans-serif;
    font-weight: normal;
    font-size: 28px;
    text-align: left;
  }

  .btn {
    background-color: #444444;
    border: none;
    color: white;
    padding: 10px 20px;
    text-align: center;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 4px 2px;
    cursor: pointer;
  }

  .foot {
    font-family: "Verdana", "Arial", sans-serif;
    font-size: 20px;
    position: absolute;
    height: 30px;
    text-align: center;
    color: #AAAAAA;
    line-height: 20px;
    width: 97%;
    top: 94%;
  }

  #Home {
    display: block;
  }

  table tr:first-child th:first-child {
    border-top-left-radius: 5px;
  }

  table tr:first-child th:last-child {
    border-top-right-radius: 5px;
  }

  table tr:last-child td:first-child {
    border-bottom-left-radius: 5px;
  }

  table tr:last-child td:last-child {
    border-bottom-right-radius: 5px;
  }


  /* Full-width input fields */
  input[type=text],
  input[type=password] {
    width: 100%;
    padding: 12px 20px;
    margin: 8px 0;
    display: inline-block;
    border: 1px solid #ccc;
    box-sizing: border-box;
  }

  /* Set a style for all buttons */
  .btn {
    background-color: #04AA6D;
    /* color: white; */
    padding: 14px 20px;
    margin: 8px 0;
    border: none;
    cursor: pointer;
  }

  button:hover {
    opacity: 0.8;
  }

  /* Extra styles for the cancel button */
  .cancelbtn {
    width: auto;
    padding: 10px 18px;
    background-color: #f44336;
  }





  span.psw {
    float: right;
    padding-top: 16px;
  }

  /* The Modal (background) */
  .modal {
    display: none;
    /* Hidden by default */
    position: fixed;
    z-index: 1;
    left: 0;
    top: 180px;
    width: 100%;
  }

  /* Modal Content/Box */
  .modal-content {

    background-color: #fefefe;
    margin: 5% auto 15% auto;
    /* 5% from the top, 15% from the bottom and centered */
    border: 1px solid #888;
    width: 80%;
    /* Could be more or less, depending on screen size */
  }




  /* Add Zoom Animation */
  .animate {
    -webkit-animation: animatezoom 0.6s;
    animation: animatezoom 0.6s
  }

  @-webkit-keyframes animatezoom {
    from {
      -webkit-transform: scale(0)
    }

    to {
      -webkit-transform: scale(1)
    }
  }

  @keyframes animatezoom {
    from {
      transform: scale(0)
    }

    to {
      transform: scale(1)
    }
  }

  /* Change styles for span and cancel button on extra small screens */
  @media screen and (max-width: 300px) {
    span.psw {
      display: block;
      float: none;
    }

    .cancelbtn {
      width: 100%;
    }
  }
</style>

<body style="background-color: #efefef" onload="process()">

  <header>
    <div class="navbar fixed-top">
      <div class="container">
        <div class="heder-right">
          <div class="navtitle">Parking System </div>
        </div>
        <div class="heder-left">
          <div class="navdata" id="date">mm/dd/yyyy</div>
          <div class="navheading">Date</div><br>
          <div class="navdata" id="time">00:00:00</div>
          <div class="navheading">TIME</div>
        </div>


      </div>
    </div>
  </header>

  <div class="tab">
    <button class="tablinks" onclick="openCity(event, 'Home')">Home</button>
    <button class="tablinks" onclick="openCity(event, 'Admin')">Admin</button>
  </div>


  <main id="Home" class="container tabcontent active">
    <div class="category">System Monitor</div>
    <div style="border-radius: 10px !important;">
      <table style="width:50%">
        <colgroup>
          <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
        </colgroup>
        <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2" style="background-color:rgb(0,0,0); color:#FFFFFF">
        <tr>
          <th colspan="1">
            <div class="heading">Input</div>
          </th>
          <th colspan="1">
            <div class="heading">Value</div>
          </th>

        </tr>
        <tr>
          <td>
            <div class="bodytext">Number Of Cars</div>
          </td>
          <td>
            <div class="tabledata" id="b0"></div>
          </td>

        </tr>
        <tr>
          <td>
            <div class="bodytext">Entry Sernsor Distance</div>
          </td>
          <td>
            <div class="tabledata" id="b1"></div>
          </td>

        </tr>

        <tr>
          <td>
            <div class="bodytext">Exit Sernsor Distance</div>
          </td>
          <td>
            <div class="tabledata" id="b2"></div>
          </td>

        </tr>

      </table>
    </div>


    <br>

    <br>
    <br>

    <br>
    <br>
  </main>




  <div id="Admin" class="tabcontent">



    <div class="admin-content" style="display: none;">

      <div class="category"> System Control:</div>
      <br>
      <div class="bodytext"> System Status:</div>
      <button type="button" class="btn" id="btn0" onclick="ButtonPress0()">Toggle</button>
      <p id="status-noti"></p>

      <div class="bodytext">Reset Cars Number:</div>
      <button type="button" class="btn" id="btn1" onclick="ButtonPress1()">Reset</button>
      <p id="reset-noti"></p>

      <div class="bodytext">Open Entery Gate:</div>
      <button type="button" class="btn" id="btn2" onclick="ButtonPress2()">Open</button>
      <p id="open-noti"></p>

      <div class="bodytext">Open Exit Gate:</div>
      <button type="button" class="btn" id="btn3" onclick="ButtonPress3()">Open</button>
      <p id="exit-noti"></p>

          <div class="bodytext">Restart The System:</div>
      <button type="button" class="btn" id="btn3" onclick="RestartBtn()">Restart</button>
      <p id="restart-noti"></p>





    </div>

    <div class="login-model">
      <button class="btn" onclick="document.getElementById('id01').style.display='block'" style="width:auto;">Login</button>
      <div id="id01" class="modal">

        <div class="modal-content animate">
          <div class="container">
            <label for="psw"><b>Password</b></label>
            <input id="pass" type="password" placeholder="Enter Password" name="psw" required>
            <button class="btn" type="submit" onclick="checkPass()">Login</button>
            <label>
          </div>
          <div class="container" style="background-color:#f1f1f1">
            <button type="button" onclick="document.getElementById('id01').style.display='none';"
              class="cancelbtn">Cancel</button>
          </div>
        </div>
      </div>
    </div>
  </div>

  <footer div class="foot" id="temp">The trial version of the smart parking system</div>
  </footer>

</body>

<script type="text/javascript">

  // Get the modal
  var modal = document.getElementById('id01');
  function checkPass() {
    if (document.querySelector('#pass').value == 'root') {
      document.querySelector('.login-model').style.display = "none";
      document.querySelector(".admin-content").style.display="block";

    }
  }
  // When the user clicks anywhere outside of the modal, close it
  window.onclick = function (event) {
    if (event.target == modal) {
      modal.style.display = "none";
    }
  }


  function openCity(evt, cityName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
      tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
      tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(cityName).style.display = "block";
    evt.currentTarget.className += " active";
  }


  // global variable visible to all java functions
  var xmlHttp = createXmlHttpObject();
  // function to create XML object
  function createXmlHttpObject() {
    if (window.XMLHttpRequest) {
      xmlHttp = new XMLHttpRequest();
    }
    else {
      xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlHttp;
  }
  // function to handle button press from HTML code above
  // and send a processing string back to server
  // this processing string is use in the .on method
  function ButtonPress0() {
    var xhttp = new XMLHttpRequest();
    var message;
    // if you want to handle an immediate reply (like status from the ESP
    // handling of the button press use this code
    // since this button status from the ESP is in the main XML code
    // we don't need this
    // remember that if you want immediate processing feedbac you must send it
    // in the ESP handling function and here
    xhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("status-noti").innerHTML = this.responseText;
        if (this.responseText == 'on' || this.responseText == 'off') {
          document.getElementById("status-noti").innerHTML = "SYSTEM STATUS TOGGLE SUCCESSFULLY";
          document.getElementById("status-noti").style.color = 'green';
          if (this.responseText == 'on') {
            document.getElementById("btn0").innerHTML = "Turn OFF";
          }
          else {
            document.getElementById("btn0").innerHTML = "Turn ON";
          }
        }
        else {
          document.getElementById("status-noti").innerHTML = "THERE IS A CAR TRY ENTER OR EXIT";
          document.getElementById("status-noti").style.color = 'red';
        }

      }
    }

    xhttp.open("PUT", "BUTTON_0", false);
    xhttp.send();
  }

  function ButtonPress1() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
      console.log(this.responseText);

      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("reset-noti").innerHTML = this.responseText;
        if (this.responseText == 'true') {
          document.getElementById("reset-noti").innerHTML = "CARS RESET SUCCESSFULLY";
          document.getElementById("reset-noti").style.color = 'green';
        }
        else {
          document.getElementById("reset-noti").innerHTML = "THERE IS A CAR TRY ENTER OR EXIT";
          document.getElementById("reset-noti").style.color = 'red';
        }

      }
    }


    xhttp.open("PUT", "BUTTON_1", false);
    xhttp.send();
  }


  function ButtonPress2() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {

      if (this.readyState == 4 && this.status == 200) {
        if (this.responseText == 'true') {
          document.getElementById("open-noti").innerHTML = "GATE OPEN SUCCESSFULLY";
          document.getElementById("open-noti").style.color = 'green';
        }
        else {
          document.getElementById("open-noti").innerHTML = "THERE IS A CAR TRY ENTER OR EXIT";
          document.getElementById("open-noti").style.color = 'red';
        }

      }
    }


    xhttp.open("PUT", "BUTTON_2", false);
    xhttp.send();
  }

    function RestartBtn() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {

      if (this.readyState == 4 && this.status == 200) {
        if (this.responseText == 'true') {
          document.getElementById("restart-noti").innerHTML = "SYSTEM WILL BE RESTART SOON";
          document.getElementById("restart-noti").style.color = 'green';
        }
        else {
          document.getElementById("restart-noti").innerHTML = "THERE IS A CAR TRY ENTER OR EXIT";
          document.getElementById("restart-noti").style.color = 'red';
        }

      }
    }


    xhttp.open("PUT", "restart", false);
    xhttp.send();
  }

  
  function ButtonPress3() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {

      if (this.readyState == 4 && this.status == 200) {
        if (this.responseText == 'true') {
          document.getElementById("exit-noti").innerHTML = "GATE OPEN SUCCESSFULLY";
          document.getElementById("exit-noti").style.color = 'green';
        }
        else {
          document.getElementById("exit-noti").innerHTML = "THERE IS A CAR TRY ENTER OR EXIT";
          document.getElementById("exit-noti").style.color = 'red';
        }

      }
    }


    xhttp.open("PUT", "BUTTON_3", false);
    xhttp.send();
  }

  function UpdateSlider(value) {
    var xhttp = new XMLHttpRequest();
    // this time i want immediate feedback to the fan speed
    // yea yea yea i realize i'm computing fan speed but the point
    // is how to give immediate feedback
    xhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        // update the web based on reply from  ESP
        document.getElementById("fanrpm").innerHTML = this.responseText;
      }
    }
    // this syntax is really weird the ? is a delimiter
    // first arg UPDATE_SLIDER is use in the .on method
    // server.on("/UPDATE_SLIDER", UpdateSlider);
    // then the second arg VALUE is use in the processing function
    // String t_state = server.arg("VALUE");
    // then + the controls value property
    xhttp.open("PUT", "UPDATE_SLIDER?VALUE=" + value, true);
    xhttp.send();
  }
  // function to handle the response from the ESP
  function response() {
    var message;
    var barwidth;
    var currentsensor;
    var xmlResponse;
    var xmldoc;
    var dt = new Date();
    var color = "#e8e8e8";

    // get the xml stream
    xmlResponse = xmlHttp.responseXML;

    // get host date and time
    document.getElementById("time").innerHTML = dt.toLocaleTimeString();
    document.getElementById("date").innerHTML = dt.toLocaleDateString();

    // A0
    xmldoc = xmlResponse.getElementsByTagName("B0"); //bits for A0
    message = xmldoc[0].firstChild.nodeValue;

    if (message > 10) {
      color = "#aa0000";
    }
    else {
      color = "#0000aa";
    }

    barwidth = message / 40.95;
    document.getElementById("b0").innerHTML = message;
    document.getElementById("b0").style.width = (barwidth + "%");
    // if you want to use global color set above in <style> section
    // other wise uncomment and let the value dictate the color
    document.getElementById("b0").style.backgroundColor = color;
    //document.getElementById("b0").style.borderRadius="5px";


    // A1
    xmldoc = xmlResponse.getElementsByTagName("B1");
    message = xmldoc[0].firstChild.nodeValue;
    if (message > 100) {
      color = "#aa0000";
    }
    else {
      color = "#0000aa";
    }

    document.getElementById("b1").innerHTML = message;
    width = message / 40.95;
    //document.getElementById("b1").style.width = (width + "%");
    document.getElementById("b1").style.backgroundColor = color;
    //document.getElementById("b1").style.borderRadius="5px";


    xmldoc = xmlResponse.getElementsByTagName("B2");
    message = xmldoc[0].firstChild.nodeValue;
    if (message > 100) {
      color = "#aa0000";
    }
    else {
      color = "#0000aa";
    }

    document.getElementById("b2").innerHTML = message;
    width = message / 40.95;
    //document.getElementById("b1").style.width = (width + "%");
    document.getElementById("b2").style.backgroundColor = color;


    xmldoc = xmlResponse.getElementsByTagName("LED");
    message = xmldoc[0].firstChild.nodeValue;





  }

  // general processing code for the web page to ask for an XML steam
  // this is actually why you need to keep sending data to the page to 
  // force this call with stuff like this
  // server.on("/xml", SendXML);
  // otherwise the page will not request XML from the ESP, and updates will not happen
  function process() {

    if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
      xmlHttp.open("PUT", "xml", true);
      xmlHttp.onreadystatechange = response;
      xmlHttp.send(null);
    }
    // you may have to play with this value, big pages need more porcessing time, and hence
    // a longer timeout
    setTimeout("process()", 100);
  }


</script>

</html>
)=====";
