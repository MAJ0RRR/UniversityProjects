<!doctype html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/style.css">
    <link rel="stylesheet" type="text/css" href="static/css/tabs.css">
    <link href="https://fonts.googleapis.com/css2?family=Quattrocento:wght@400;700&display=swap" type="text/css" rel="stylesheet">
    <link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/themes/smoothness/jquery-ui.css" type="text/css">
    <script src="https://code.jquery.com/jquery-1.12.4.js"></script>
    <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.js"></script>
    <script type="text/javascript" src="static/scripts/tabs.js"></script>
    <script type="text/javascript" src="static/scripts/notes.js"></script>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <header>
        <div id="logo">

            <?php if(isset($_SESSION['logged'])): ?>
                <p> Witaj <?= $_SESSION['name'] ?> !</p>
                <a id="register_button" href="logout">Wyloguj</a>
            <?php else: ?>
                <a id="register_button" href="register">Zarejestruj się</a>
                <a id="register_button" href="login">Zaloguj się</a>
            <?php endif ?>


            <h1>HISTORIA</h1>
        </div>
        <nav id="top_nav">
            <div class="nav_option"><a href="/">Strona główna</a></div>
            <div class="nav_option"><a href="epoki">Epoki historyczne</a></div>
            <div class="nav_option"><a href="postacie">Postacie historyczne</a></div>
            <div class="nav_option"><a href="kontakt">Kontakt</a></div>
        </nav>
    </header>
    <main>
        <div id="tabs">
            <ul>
                <li><a href="#fragment-1">Kontakt telefoniczny</a></li>
                <li><a href="#fragment-2">Kontakt mailowy</a></li>
                <li><a href="#fragment-3">Kontakt bezpośredni</a></li>
                <li><a href="#fragment-4">Kontakt listowny</a></li>
            </ul>
            <div id="fragment-1">
                Kontakt telefoniczny ze mną jest możliwy od poniedziałku do Soboty w godzinach 15:00 - 21:00 pod numerem +48 XXX XXX XXX.
            </div>
            <div id="fragment-2">
                Kontakt drogą mailową pod adresem xyz@mail.com.<i>Proszę podawać w tytule informacje czego konkretnie dotyczy mail!</i>
            </div>
            <div id="fragment-3">
                Z racji na obecną sytuację epidemiologiczną spotkania bezpośrednie tymczasowo wstrzymane.
            </div>
            <div id="fragment-4">
                Jeśli chcesz skontaktować się ze mną listownie,tutaj masz adres:
                <br><br>
                Sebastian Leśniewski
                123-45 Gdańsk
                ul.Gdańska 12/3
            </div>
        </div>
        <h1 class="short_article">Poniżej jest miejsce na Twoje notatki dotyczące spotkań</h1>
            <div id="note_input">
            <input type="text" placeholder="Napisz coś..." id="my_note">
             </div>
            <div id="note_input">
                <button class="button" onclick="add_note();">Dodaj notatke</button>
             </div>
        <div id="notepad"></div>
    </main>
</body>
</html>