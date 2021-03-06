<!doctype html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>WAI</title>
    <link rel="stylesheet" type="text/css" href="static/css/style.css">
    <link href="https://fonts.googleapis.com/css2?family=Quattrocento:wght@400;700&display=swap" type="text/css" rel="stylesheet">
    <script src="static/scripts/jquery-3.5.1.min.js" type="text/javascript"></script>
    <script src="static/scripts/slider.js" type="text/javascript"></script>
    <noscript>
        <style>
            #slider {
                display: none;
            }
        </style>
    </noscript>
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
        <div class="slider">
            <figure>
                <img src="static/images/slider/1.png" />
                <img src="static/images/slider/2.png" />
                <img src="static/images/slider/3.png" />
                <img src="static/images/slider/4.png" />
                <img src="static/images/slider/5.png" />
                <img src="static/images/slider/6.png" />
            </figure>
            <button class="prev-button">&larr;</button>
            <button class="next-button">&rarr;</button>
        </div>
        <article>
            <section class="short_article">
                <h1>Słów kilka o epokach historycznych</h1>
                <p>
                    Prehistoria czasy sprzed wynalezienia pisma. Epokę datuje się od momentu pojawienia się pierwszych ludzi na Ziemi (ok. 4 mln lat temu, a człowiek podobny do współczesnego ok. 2,5 tysięcy lat temu), do około XXX w. p.n.e. (ok. 3000r. p.n.e.). Ziemia liczyła wówczas około 4 mld lat. W Afryce około 5 milionów lat temu żył pierwszy z gatunków praludzi - australopitek. Po nim następowały kolejne formy ewolucji: Homo Erectus, który jako pierwszy posługiwał się ogniem, następnie Neandertalczyk, który był pierwszym człowiekowatym posługującym się mową, aż do człowieka współczesnego Homo Sapiens, którego ekspansja rozpoczęła się 60 - 50 tyś. lat temu. W efekcie procesu przeobrażania się gatunków, praludzie osiągali coraz większy wzrost, ich sylwetka była bardziej wyprostowana, a skóra - mniej owłosiona. Jedna z najistotniejszych zmian jaka nastąpiła w Prehistorii, było przekształcenie trybu życia ludzkości z koczowniczego na osiadły, nazywana też rewolucją neolityczna.
                    <br><br>
                    Starożytność  (Antyk) datuje się od około XXX w. p.n.e. (pojawienie się pisma), aż do roku 476 kiedy nastąpił upadek imperium zachodniorzymskiego i przejęcie władzy przez barbarzyńskiego Władcę Odoakra. Epoka ta obejmuje okresy dotyczące Starożytnego Egiptu, kultur Bliskiego i Dalekiego Wschodu oraz cywilizacji starożytnej Grecji i Rzymu, jak też czasy tzw. starożytności chrześcijańskiej, trwające od I do V wieku n.e. Państwo faraonów rozwinęło się u wybrzeży Nilu, życie Egipcjan układało się w rytmie wylewów rzeki. Egipski kalendarz powstał około 3000 lat p.n.e. Podwaliny kultury starożytnej Grecji zawdzięczamy dwóm ośrodkom – Mykenom oraz Krecie. Grecy, podobnie jak Egipcjanie, wyznawali wielu Bogów, którzy według mitów, zamieszkiwali górę Olimp. Na terenach Grecji powstawały polis – (miasta - państwa), tworzące specyficzną formę ustroju. Starożytna Grecja miała też ogromny wpływ na Imperium Rzymskie. Należy również wspomnieć o dziejach Izraela. Najstarsze przekazy o początkach państwowości Izraela daje nam Biblia. Żydzi byli koczowniczym narodem, żyjącym w dużych rodzinach, wędrującym ze stadami bydła od Syrii przez Mezopotamię aż do Egiptu, gdzie zostali zatrzymani siłą przez faraona.
                    <br><br>
                    Średniowiecze z łac. medium aevum, media aetas - wieki średnie. Zakładano, że jest to tylko okres przejściowy pomiędzy Starożytnością a Renesansem, który nie wniesie niczego znaczącego do historii. Do dziś funkcjonuje zwrot „nie żyjemy w średniowieczu”, który wskazuje na zacofanie tej epoki. Jest to jednak pogląd błędny. Średniowiecze było okresem nie tylko długim (trwało aż 1000 lat od V do XV wieku), w którym wiele się wydarzyło, ale przed wszystkim zasadniczo wpłynęło na późniejszą literaturę, może poszczycić się osiągnięciami w zakresie nauki i sztuki. Początek epoki to druga połowa V w. n.e. - datą umowną jest rok 476 - upadek Cesarstwa Zachdnio-rzymskiego. Jako zakończenie okresu podaje się dwie daty, rok 1453 - zdobycie przez Turków Konstantynopola oraz rok 1492 - odkrycie Ameryki przez Krzysztofa Kolumba. Średniowiecze to okres, w którym Kościół, Papieże- głowy Kościoła, odgrywali bardzo ważną rolę w życiu politycznym, społecznym i kulturowym. Najistotniejszym wydarzeniem był podział chrześcijaństwa na dwa odłamy – zachodnie, łacińskie oraz wschodnie, bizantyjskie (schizma wschodnia z 1054 roku). Średniowiecze w Polsce rozpoczyna przyjęcie chrztu przez Mieszka I w 966 r., włączenie Polski do grona Państw chrześcijańskich Europy. Do najważniejszych wydarzeń zaliczą się również początki polskiej organizacji państwowej, ukształtowanie się pierwszego sejmu jako ogólnopolskiej władzy przedstawicielskiej za Jana Olbrachta oraz uchwalenie przez sejm walny Konstytucji Nihil Novi.
                    <br><br>
                    Nowożytność rozpoczęła się w 2 połowie XV w. Epoka dzieli się na Wczesną Nowożytność, która kończy się w 1798 r. - wybuchem Wielkiej Rewolucji Francuskiej oraz na Wiek XIX, którego koniec datuje się na rok 1914 - wybuch Pierwszej Wojny Światowej. Obie daty określające koniec średniowiecza i początek nowożytności ( Upadek Konstantynopola, Odkrycie Ameryki przez Kolumba) są czysto umowne. Upadek Bizancjum miał ograniczony wpływ na kulturę europejską, a wyprawy z Europy w kierunku zachodnim i południowym miały przynieść skutki dopiero w XVI. Realnymi wyznacznikami przejścia od epoki średniowiecznej do nowożytnej są natomiast przemiany kulturowe, polityczne, państwowe oraz ideologiczne. Nowożytność dzieli się na następujące okresy:
                    Renesans - od XV do XVI wieku
                    Barok - od końca XVI wieku do początków XVIII wieku
                    Oświecenie - epoka przypadająca na XVIII wiek
                    Romantyzm - głównie w literaturze, pierwsza połowa XIX wieku
                    W periodyzacji odnoszącej się do dziejów Polski za początek nowożytności uznaje się rok 1492 - śmierć króla Kazimierza Jagiellończyka. Historia nowożytna Polski, to historia Polski szlacheckiej, przedrozbiorowej. Za jedno z najważniejszych wydarzeń oraz zakończenie okresu powszechnie uznaje się III rozbiór Polski w 1795.
                    <br><br>
                    Czasy współczesne (Historia najnowsza) - za daty początkowe przyjmuje się najczęściej rok 1789 - rewolucja francuska lub rok 1815 - kongres wiedeński. W Polsce przyjęło się liczyć od trzeciego rozbioru Rzeczypospolitej w 1795 r. Historie najnowszą dzieli się na następujące okresy:
                    I wojna światowa i okres międzywojenny - od 1914 do 1939 roku
                    Pierwsze cztery lata tego okresu to I Wojna Światowa, następnie etap międzywojenny, wzrost znaczenia USA i ZSRR . Są to również lata gdy na mapę Europy wróciła Polska.
                    II wojna światowa - od 1939 do 1945 roku
                    Wszystkie działania wojenne od kampanii wrześniowej po kapitulację Niemiec i Japonii w 1945 roku.
                    Powojnie - od 1945 do dzisiaj
                    Na świecie to epoka zimnej wojny, aż do upadku muru berlińskiego. W Polsce to okres PRL-u, a następnie transformacja ustrojowa.
                </p>
            </section>
            <section>
                <table>
                    <tr>
                        <th>Epoka</th>
                        <th>Okres trwania</th>
                        <th>Osoby kojarzone z epoką</th>
                    </tr>
                    <tr>
                        <td>Prehistoria</td>
                        <td>Początek ludzkości - ok. 4000/3500 roku p.n.e</td>
                        <td>?</td>
                    </tr>
                    <tr>
                        <td>Starożytność</td>
                        <td>ok. 4000/3500 roku p.n.e - 476 rok p.n.e</td>
                        <td>Aleksander Wielki</td>
                    </tr>
                    <tr>
                        <td>Średniowiecze</td>
                        <td>476 rok n.e - 1453 rok n.e</td>
                        <td>Karol Wielki</td>
                    </tr>
                    <tr>
                        <td>Nowożytność</td>
                        <td>1492 rok n.e - 1789 rok n.e</td>
                        <td>Lonardo Da Vinci</td>
                    </tr>
                    <tr>
                        <td>Epoka XIX wieku</td>
                        <td>1789 rok n.e - 1914 rok n.e </td>
                        <td>Napoleon Bonaparte</td>
                    </tr>
                    <tr>
                        <td>Współczesność</td>
                        <td>1914 rok n.e - dziś</td>
                        <td>Stephen Hawking</td>
                    </tr>
                </table>
            </section>
        </article>
    </main>
    <div id="footer">
        WAI - Sebastian Leśniewski,Wszelkie prawa zastrzeżone &copy;
    </div>
</body>
</html>