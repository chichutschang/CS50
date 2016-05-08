<?php

    // configuration
    require("../includes/config.php"); 

    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {

        //pulls symbol, shares from portfolio table in SQL database
        $rows = CS50::query("SELECT symbol, shares FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
        if($rows === false)
        {
            apologize("Can't find your portfolio");
        }

        $positions = [];
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            {
                if($stock !== false)
                {
                    $positions[] = [
                        "name" => $stock["name"],
                        "price" => number_format($stock["price"], 2),
                        "shares" => number_format($row["shares"], 0),
                        "symbol" => $row["symbol"],
                        "total" => number_format($stock["price"] * $row["shares"], 2),
                    ];
                }
            }    
        }
        //pulls cash from users table in SQL database
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $usercash = number_format($cash[0]["cash"],2);
        
        // render portfolio
        render("portfolio.php", ["cash" => $usercash, "positions" => $positions, "title" => "Portfolio"]);
            
    }
?>
