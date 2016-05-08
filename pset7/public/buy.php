<?php

    // configuration
    require("../includes/config.php"); 

    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
        // check if there is stock in portfolio
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }    
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares");
        }    
        else if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
           apologize("Invalid number of shares");
        }

        // capitalize stock symbol
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
    
        //lookup stock
        $stock = lookup($_POST["symbol"]);
        
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?" , $_SESSION["id"]);
        $cash = $rows[0]["cash"];
        
        $cost = $_POST["shares"] * $stock["price"];
        
        if ($cost >= $cash)
        {
            apologize("You can't afford that");
        }

        else
        {
            //insert stock into portfolio table in SQL database
            CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES( ?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
        
            //update cash in users database
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);

            //update history
            CS50::query("INSERT INTO history(user_id, transaction, date_time, symbol, shares, price) VALUES(?, 'BUY', Now(), ?, ?, ?)", $_SESSION["id"], $stock["symbol"], $_POST["shares"], $stock["price"]);
        }
        
        
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
<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="shares" placeholder="Shares" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Buy</button>
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
