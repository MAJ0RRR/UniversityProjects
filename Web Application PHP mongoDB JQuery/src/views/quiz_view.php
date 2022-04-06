<!doctype html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/style.css" />
    <link rel="stylesheet" type="text/css" href="static/css/quiz.css" />
    <link href="https://fonts.googleapis.com/css2?family=Quattrocento:wght@400;700&display=swap" type="text/css" rel="stylesheet">
    <script src="../web/static/scripts/jquery-3.5.1.min.js"></script>
    <script type="text/javascript" src="static/scripts/script.js"></script>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="IE=edge"> 
</head>
<body>
    <header>
        <div id="logo">
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
        <section>
            <div id="quiz">
                <div class="title">
                    <h1>Quiz</h1>
                    A więc myślisz że wiesz już wystarczająco dużo, aby podjąć się quizu ? Sprawdźmy to!
                </div>
                <button onclick="highscore()" class="button">Pokaż najwyższy wynik</button>
                <div id="high_score"></div>
                <div id="quiz">
                    <form method="POST" id="quiz_form" enctype="multipart/form-data" onsubmit="count_score(5)">
                        <div class="question">
                            Jak zginął cesarz Fryderyk Barbarossa ?
                            <div class="answer">
                                <ol>
                                    <li>
                                        <label><input type="radio" name="q1" value="0" />W bitwie raniony włócznią przez swojego żołnierza</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q1" value="0" />Zginął od obrażeń odniesionych od ostrzału dział</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q1" value="0" />Został otruty przez swojego zazdrosnego brata</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q1" value="1" />Utonął w przeprawie swoich wojsk przez rzekę</label>
                                    </li>
                                </ol>
                            </div>
                        </div>
                        <div class="question">
                            Które z tych zwierząt żyło na Ziemii,gdy budowano piramidy w Gizie?
                            <div class="answer">
                                <ol>
                                    <li>
                                        <label><input type="radio" name="q2" value="1" />Mamut Włochaty</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q2" value="0" />Leniwiec Olbrzymi</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q2" value="0" />Tygrys Szablozębny</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q2" value="0" />Titanboa</label>
                                    </li>
                                </ol>
                            </div>
                        </div>
                        <div class="question">
                            Ile lat miał Aleksander Macedoński podbijając Persję?
                            <div class="answer">
                                <ol>
                                    <li>
                                        <label><input type="radio" name="q3" value="0" />29</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q3" value="1" />25</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q3" value="0" />33</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q3" value="0" />35</label>
                                    </li>
                                </ol>
                            </div>
                        </div>
                        <div class="question">
                            Dlaczego Mongolii nie udało się podbić Japonii w XIII wieku?
                            <div class="answer">

                                <ol>
                                    <li>
                                        <label><input type="radio" name="q4" value="0" />Bali się samurajów,uważali ich za demony</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q4" value="0" />Nie potrafili konstruować łodzi</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q4" value="1" />Tajfun zatopił ich flotę</label>
                                    </li>
                                    <li>
                                        <label><input type="radio" name="q4" value="0" />Ich technologia była zbyt prymitywna</label>
                                    </li>
                                </ol>
                            </div>
                        </div>
                        <div class="question">
                            Któremu z tych Państw Polska wypowiedziała wojnę?
                            <div class="answer">
                                <ol>
                                    <li>
                                        <label> <input type="radio" name="q5" value="0" />Argentyna</label>
                                    </li>
                                    <li>
                                        <label> <input type="radio" name="q5" value="0" />Jamajka</label>
                                    </li>
                                    <li>
                                        <label> <input type="radio" name="q5" value="0" />Haiti</label>
                                    </li>
                                    <li>
                                        <label> <input type="radio" name="q5" value="1" />Japonia</label>
                                    </li>
                                </ol>
                            </div>
                        </div>
                        <div id="controls">
                            <input value="Wyślij" class="button" type="submit" />
                            <input value="Resetuj" class="button" type="reset" />
                        </div>
                    </form>
                </div>
            </div>
        </section>
        <div id="dialog">
            <div id="final1"></div>
            <div id="final2"></div>
            <button class="button" id="zapisz" onclick="save()">Zapisz wynik</button>
            <button class="button" id="zamknij" onclick="hide()">Zamknij</button>
        </div>
    </main>
    <footer>
        <div id="footer">
            WAI - Sebastian Leśniewski,Wszelkie prawa zastrzeżone &copy;
        </div>
    </footer>
</body>
</html>