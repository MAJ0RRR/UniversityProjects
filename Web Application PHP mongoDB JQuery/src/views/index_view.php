<!doctype html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/style.css">
    <link rel="stylesheet" type="text/css" href="static/css/clock.css">
    <link rel="stylesheet" type="text/css" href="static/css/accordion.css">
    <script src="https://code.jquery.com/jquery-1.12.4.js"></script>
    <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.js"></script>
    <script type="text/javascript" src="static/scripts/clock.js"></script>
    <script type="text/javascript" src="static/scripts/accordion.js"></script>
    <noscript>
        <style>
            #clock {
                display: none;
            }

            #index-quiz {
                display: none;
            }

            .short {
                display: none;
            }
        </style>
    </noscript>
    <link href="https://fonts.googleapis.com/css2?family=Quattrocento:wght@400;700&display=swap" type="text/css" rel="stylesheet">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body onload="clock();">
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
        <nav>
            <div id="top_nav">
                <div class="nav_option"><a href="/">Strona główna</a></div>
                <div class="nav_option"><a href="epoki">Epoki historyczne</a></div>
                <div class="nav_option"><a href="postacie">Postacie historyczne</a></div>
                <div class="nav_option"><a href="kontakt">Kontakt</a></div>
            </div>
        </nav>
    </header>
        <div id="clock"></div>
    <main>
        <artcile>
            <div class="short_article">
                <h1>Witaj na mojej stronie!</h1>
                <p>
                   Jest ona poświęcona mojemu hobby jakim jest historia,od kiedy tylko pamiętam fascynowałem się rycerzami,czołgami i starożytnym cywilizacjami.Uwielbiam poznawać życie naszych przodków,próbować zrozumieć świat oczami zwykłego człowieka,od któego dzieli mnie kilka epok.Bardzo dużo rzeczy można się w ten sposób dowiedzieć o dzisiejszym świecie.Historia to nie tylko kojarzące nam się ze szkoły wkuwanie dat na najbliższą kartkówkę.Historia pozwala nam analizować przeszłość, a zatem uczyć się czegoś nowego.Tak samo jak pojedynczy człowiek uczy się na błędach,tak również uczy się cała cywilizacja,oczywiście nie zawsze tak niestety jest.Poznając coraz dokładniej historię powoli zaczynamy dostrzegać schematy,które się w niej powtarzają i czasami bywa to naprawdę niepokojące,zwłaszcza w dzisiejszych niepewnych czasach...
                    <br><br>
                    Na stronie znajdziesz mnóstwo przydatnych informacji,które może zrobią z Ciebie jeszcze pasjonata historii! Możesz spróbować swoich sił w quizie historycznym i zapisać swój wynik,sprawdzić nadchodzące eventy.Dodatkowo możesz przejrzeć galerię moich ulubionych postaci historycznych i przy okazji poczytać trochę o nich.Znajduje się tu również podstrona z epokami historycznymi,która może wydawać się trochę nudna,ale taki jest wymó dobrej znajomości historii,że jednak ramy czasowe trzeba kojarzyć,nie przedłużając miłego surfowania :-)
                </p>
            </div>
            <div id="accordion">
                <h3>&rarr; Moje ulubione strony poświęcone historii &larr;</h3>
                <div>
                    <ul>
                        <li><a href="https://www.youtube.com/channel/UCRWskElXZvb3q0W5JopPTnQ">&rarr;Historia bez Cenzury</a></li>
                        <li><a href="https://ciekawostkihistoryczne.pl/">&rarr;Ciekawostki Historyczne</a></li>
                        <li><a href="https://wielkahistoria.pl/">&rarr;Wielka Historia</a></li>
                        <li><a href="https://dzieje.pl/">&rarr;Dzieje</a></li>
                        <li><a href="https://historia.org.pl/">&rarr;Historia org</a></li>
                    </ul>
                </div>
                <h3>&rarr; Historia się nie kończy! Przejrzyj nadchodzące eventy dla sympatyków historii &larr;</h3>
                <div>
                    <div class="history_event">
                        <p>Pokaz artylerii średniowiecznej i broni czarnoprochowej na Zamku Ogrodzieniec 15.11.2020</p>
                    </div>
                    <div class="history_event">
                        <p>XII rekonstrukcja bitew pod Tomaszowem Lubelskim 19.11.2020</p>
                    </div>
                    <div class="history_event">
                        <p>Turniej rycerski na Zamku w Liwie 02.12.2020</p>
                    </div>
                    <div class="history_event">
                        <p>III Festiwal Mitologii Słowiańskie 07.12.2020</p>
                    </div>
                    <div class="history_event">
                        <p>Obrona Zamku Tenczyn przed Szwedem 1655 19.12.2020</p>
                    </div>
                    <div class="history_event">
                        <p>III Festiwal Mitologii Słowiańskie 07.12.2020</p>
                    </div>
                    <div class="history_event">
                        <p>X Odyseja Historyczna w Leszczynku 04.02.2021</p>
                    </div>
                    <div class="history_event">
                        <p>Walka Czołgów 4 - Poligon Orzysz 18.03.2021</p>
                    </div>
                </div>
                <h3 id="index-quiz">&rarr; Chcesz się sprawdzić w quizie historycznym? &larr;</h3>
                <div class="short">
                    <p>
                        <a href="quiz">Zabierz mnie do quizu</a>
                    </p>
                </div>
            </div>
        </artcile>
    </main>
    <footer>
        <div id="footer">
            WAI - Sebastian Leśniewski,Wszelkie prawa zastrzeżone &copy;
        </div>
    </footer>
</body>
</html>