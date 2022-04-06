<!doctype html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/style.css">
    <link href="https://fonts.googleapis.com/css2?family=Quattrocento:wght@400;700&display=swap" type="text/css" rel="stylesheet">
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
        <div id="upload">
            <h2>Dodaj swoją ulubioną postać historyczną do naszej galerii!</h2>
            <form method="post" action="upload" enctype="multipart/form-data">
                <label name="photo">Zdjęcie: </label>
                <input type="file" name="photo"/>
                <br>
                <label name="watermark">Znak Wodny: </label>
                <input type="text" name="watermark"/>
                <br>
                <label name="title">Tytuł: </label>
                <input type="text" name="title" placeholder="Tytuł..."/>
                <br>
                <label name="author">Autor: </label>
                <input type="text" name="author" placeholder="Autor..."/>
                <br>
                <input type="submit" value="Wyślij"/>
            </form>
            <a href="view_gallery">Zobacz galerię!</a>
        </div>
    </main>

    <footer>
        <div id="footer">
            WAI - Sebastian Leśniewski,Wszelkie prawa zastrzeżone &copy;
        </div>
    </footer>
</body>
</html>