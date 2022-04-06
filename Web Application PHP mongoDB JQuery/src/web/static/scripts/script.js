window.addEventListener('DOMContentLoaded', if_send);
function check(n) {
    var answer = new Array(n);
    var score = 0;
    var form = new FormData(quiz_form);
    for (var i = 0; i < n; i++) {
        answer[i] = form.get("q" + (i + 1));
    }
     for (var i = 0; i < n; i++) {
        if (answer[i] == null) answer[i] = 0;
        score += parseInt(answer[i]);
    }
    return score;
}
function count_score(n) {
    var score = check(n);
    var max_score = sessionStorage.getItem("max_score");
    sessionStorage.setItem("send", "1");
    sessionStorage.setItem("score", score);
    if (score > max_score) sessionStorage.setItem("max_score", score);
}

function if_send() {
    var i = sessionStorage.getItem("send");
    if (i == "1") {
        var score = sessionStorage.getItem("score");
        var max_score = sessionStorage.getItem("max_score");
        if (max_score == null) max_score = 0;
        document.getElementById("final1").innerHTML = ("Masz poprawne " + score + "/5 odpowiedzi");
        document.getElementById("final2").innerHTML = ("Najlepszy wynik podczas sesji: " + max_score);
        dialog.style.display = "block";
    }
}
function hide() {
    sessionStorage.setItem("send", "0");
    var dialog = document.getElementById("dialog");
    dialog.style.display = "none";
}
function save() {
    var score = sessionStorage.getItem("score");
    localStorage.setItem("highscore", score);
    hide();
}

function highscore() {
    var highscore = localStorage.getItem("highscore");
    document.getElementById("high_score").innerHTML = "Najlepszy wynik: " + highscore;
}