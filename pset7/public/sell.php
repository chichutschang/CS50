<?php

    // configuration
    require("../includes/config.php");
        
    // pulls data from server
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //get # of shares
        $symbols = CS50::query("SELECT symbol FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
        
        //checks for stocks in portfolio
        if ($symbols === false)
        {
            apologize("You don't own that stock.");
        }

        else 
        {
            render("sell_form.php", ["symbols" => $symbols, "title" => "Sell"]);
        }
        
    }    
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check if there is stock in portfolio
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell.");
        }

        //lookup stock
        $stock = lookup($_POST["symbol"]);

        //calculate value of stock
        $shares = CS50::query("SELECT shares FROM portfolio WHERE user_id =? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

            if(count($shares) > 0)
            {
                $value = $shares[0]["shares"];
            }
            else
            {
                apologize("Nothing to sell.");
            }
        $cost = $value * $stock["price"];
       
        //delete stock from portfolio table in SQL database
        CS50::query("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        //update cash in users database
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $cost, $_SESSION["id"]);
        
        //update history
        CS50::query("INSERT INTO history(user_id, transaction, date_time, symbol, shares, price) VALUES(?, 'SELL', Now(), ?, ?, ?)", $_SESSION["id"], $stock["symbol"], $value, $stock["price"]);
        
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

                    <title>C$50 Finance: Get Quote</title>
        
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
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="symbol">
                <option value="symbol">Symbol</option>
                <?php foreach ($rows as $row): ?>
                    <option value="symbol"><?=$symbol["symbol"]?></option>
                <?php endforeach ?>

            </select>
            
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Sell</button>
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
