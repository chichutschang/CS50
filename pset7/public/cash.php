<?php

    // configuration
    require("../includes/config.php"); 

    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // check if there is stock in portfolio
        if (empty($_POST["cash"]))
        {
            apologize("You must specify amount of cash to add.");
        }    
        else if (preg_match("/^\d+$/", $_POST["cash"]) == false)
        {
           apologize("Invalid amount of cash.");
        }
        $cash = $_POST["cash"];
        
        //update cash in users database
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["cash"], $_SESSION["id"]);
        
        //send user back to index.php
        redirect("/");
    }
    
?>

<!DOCTYPE html>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/css/styles.css" rel="stylesheet"/>

        <meta content="initial-scale=1, width=device-width" name="viewport"/>

                    <title>C$50 Finance: Buy</title>
        
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
                                    <ul class="nav nav-pills">
                        <li><a href="quote.php">Quote</a></li>
                        <li><a href="cash.php">Cash</a></li>
                        <li><a href="buy.php">Buy</a></li>
                        <li><a href="sell.php">Sell</a></li>
                        <li><a href="history.php">History</a></li>
                        <li><a href="logout.php"><strong>Log Out</strong></a></li>
                    </ul>
                            </div>

            <div id="middle">
<form action="cash.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="cash" placeholder="Cash" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Add</button>
        </div>
    </fieldset>
</form>
            </div>

            <div id="bottom">
                Brought to you by the number 7.
            </div>

        </div>

    </body>

</html>
