<?php

    // configuration
    require("../includes/config.php");

    // else if user reached page via POST (as by submitting a form via POST)
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
    
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
    
        //form input: symbol the user wants to look up
        $stock = lookup($_POST["symbol"]);
        
        // ensure symbol was found
        if ($stock == false)
        {
            apologize("Symbol not found.");
            return false;
        }

        //prints name, symbol & price
        render("quote.php", ["stock" => $stock, "title" => "Quote"]);
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
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
<form action="quote.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">Get Quote</button>
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
