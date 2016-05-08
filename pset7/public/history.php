<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {

        //pulls symbol, shares from history table in SQL database
        $rows = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);

        $positions = [];
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            {
                if($stock !== false)
                {
                    $positions[] = [
                        "transaction" => $row["transaction"],
                        "date_time" => $row["date_time"],
                        "symbol" => $row["symbol"],
                        "shares" => number_format($row["shares"], 0),
                        "price" => number_format($stock["price"], 2),
                    ];
                }
            }    
        }
    }

?>

<!DOCTYPE html>

<html>

    <head>

        <!-- http://getbootstrap.com/ -->
        <link href="/css/bootstrap.min.css" rel="stylesheet"/>

        <link href="/css/styles.css" rel="stylesheet"/>

        <meta content="initial-scale=1, width=device-width" name="viewport"/>

                    <title>C$50 Finance: Portfolio</title>
        
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
<table class="table table-striped">

    <thead align ="left">
        <tr>
            <th>Transaction</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody align ="left">
        <?php foreach ($positions as $position): ?>
        <tr>
                    <td><?=$position["transaction"]?></td>
                    <td><?=$position["date_time"]?></td>
                    <td><?=$position["symbol"]?></td>
                    <td><?=$position["shares"]?></td>
                    <td>$<?=$position["price"]?></td>
        </tr>
        <?php endforeach ?>
    </tbody>    

</table>
            </div>

            <div id="bottom">
                Brought to you by the number 7.
            </div>

        </div>

    </body>

</html>
