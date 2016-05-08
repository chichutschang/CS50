<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must provide your password.");
        }

        //make sure $_POST ["password"] and $_POST["confirmation"] are the same
        if ($_POST ["password"] == $_POST ["confirmation"])
        {
            //insert a new user into SQL database
            $rows = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));

            //checks if username already exists in SQL database
            if($rows !== 1) 
            {
                apologize("That username appears to be taken");    
            }
                    
            //if no username exists in SQL database, log in the new user's ID and store in session
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
                    
            // log user in
            $_SESSION["id"] = $row["id"];

            // and redirect to portfolio
            redirect("/");    
                    
        } 
        else if ($_POST ["password"] != $_POST ["confirmation"])
        {
            apologize("Those passwords did not match!");
        }
    }
        
?>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/css/styles.css" rel="stylesheet"/>

        <meta content="initial-scale=1, width=device-width" name="viewport"/>

                    <title>C$50 Finance: Register</title>
        
        <!-- https://jquery.com/ -->
        <script src="/js/jquery-1.11.3.min.js"></script>

        <!-- http://getbootstrap.com/ -->
        <script src="/js/bootstrap.min.js"></script>

        <script src="/js/scripts.js"></script>

    </head>

 <body>
        <div class="container">

            <div id="top">
                <div>
                    <a href="/"><img alt="C$50 Finance" src="/img/logo.png"/></a>
                </div>
            </div>

            <div id="middle">

<form action="register.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="username" placeholder="Username" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="password" placeholder="Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Password (again)" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Register</button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="login.php">log in</a>
</div>
            </div>

            <div id="bottom">
                Brought to you by the number 7.
            </div>

        </div>

    </body>

</html>