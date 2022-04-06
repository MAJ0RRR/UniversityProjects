<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="static/css/style.css">
</head>

<body>
    <main>
        <div id="error">
            <p>Wygląda na to,że coś poszło nie tak!</p>
            <p><?= $_COOKIE['error'] ?></p>
            <a href="/">Wróć na stronę główną</a>
        </div>
    </main>
</body>

</html>