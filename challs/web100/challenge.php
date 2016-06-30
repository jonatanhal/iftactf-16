<?php

$FAIL = false;

function login($username, $password) {
    $flag = "iftactf16{ffbd9e70-ca8b-41a4-93e7-f6d8badce3b7}";
    $db = new mysqli("127.0.0.1", "web100", "701bab86-afc7-4543-b0fb-3276636022c2", "challenges");
    if ($db->connect_errno) {
        echo "If you see this message on your browser, the admins screwed up; please tell them so they can fix it\n\n";
        die("Failed to connect to database - " . $db->connect_errno . " : " . $db->connect_error);
    }

    $q = "SELECT USERNAME FROM db_web100 WHERE USERNAME = '" . $db->escape_string($username) . "' AND password = '" . $password ."'";
    $ok = $db->query($q);
    if ($ok) {
        $db->close();
        die("Hello " . $username . ", Your flag is: " . $flag);
    }
    $db->close();
    return "nope";
}

if ( $_SERVER['REQUEST_METHOD'] === 'GET' ) {
    if (isset($_GET['password']) || isset($_GET['username'])) {
        $FAIL = login($_GET['username'], $_GET['password']);
    }
}

$output = '<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Login</title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">
</head>
<body style="margin-top: 5%;">
<div class="container">
<div class="jumbotron">
<header>
<h3>Login</h3>
<hr>';
if ( $_SERVER['REQUEST_METHOD'] === 'GET' && $_GET['password'] == "") {
    $output .= '<p class="text-danger">Please fill out both fields</p><hr>';
} else if ($FAIL === "nope") {
    $output .= '<p class="text-danger"><marquee>Wrong password!</marquee></p><hr>';
}
$output .= '</header><form method="GET">
<div class="row">
<div class="form-group col-md-6">
<label for="username">Username</label>
<input name="username" type="text" value="';
if ( isset($_POST['username']) ) {
    $output .=  $_POST['username'] . '"';
} else {
    $output .= '"';
}

$output .= ' class="form-control" id="username">
</div>
</div>
<div class="row">
<div class="form-group col-md-6">
<label for="password">Password</label>
<input name="password" class="form-control" id="password">
</div>
</div>
<button type="submit" class="btn btn-default">Submit</button>
</form>
</div>
</div>
</body>
</html>';

echo $output;