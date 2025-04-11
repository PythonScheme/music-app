/**
 * WEB222 – Assignment 04
 *
 * I declare that this assignment is my own work in accordance with
 * Seneca Academic Policy. No part of this assignment has been
 * copied manually or electronically from any other source
 * (including web sites) or distributed to other students.
 *
 * Please update the following with your information:
 *
 *      Name:       <Renuka Gurung>
 *      Student ID: <171840234>
 *      Date:       <21st March, 2025>
 */

// All of our data is available on the global `window` object.
// Create local variables to work with it in this file.
// Updated app.js

document.addEventListener("DOMContentLoaded", function () {
    const menu = document.getElementById("menu");
    const songCardsContainer = document.getElementById("song-cards");
    const selectedArtistDisplay = document.getElementById("selected-artist");

    // Create artist buttons
    window.artists.forEach(artist => {
        let button = document.createElement("button");
        button.textContent = artist.name;
        button.addEventListener("click", () => showSongs(artist.artistId));
        menu.appendChild(button);
    });

    // Show songs for the first artist initially
    if (window.artists.length > 0) {
        showSongs(window.artists[0].artistId);
    }

    function showSongs(artistId) {
        const artist = window.artists.find(a => a.artistId === artistId);
        if (!artist) return;

        selectedArtistDisplay.textContent = artist.name;
        songCardsContainer.innerHTML = ""; // Clear previous cards

        const artistSongs = window.songs.filter(song => song.artistId === artistId && !song.explicit);

        artistSongs.forEach(song => {
            let card = document.createElement("div");
            card.classList.add("card");

            let songImg = document.createElement("img");
            songImg.src = song.imageUrl || "images/default.jpg"; // Fallback image
            songImg.alt = song.title;
            songImg.classList.add("card-image");
            songImg.addEventListener("click", () => window.open(song.link, "_blank"));

            let title = document.createElement("h3");
            title.textContent = song.title;

            let year = document.createElement("p");
            year.textContent = `Year: ${song.year}`;

            let duration = document.createElement("p");
            duration.textContent = `Duration: ${formatDuration(song.length)}`;

            card.appendChild(songImg);
            card.appendChild(title);
            card.appendChild(year);
            card.appendChild(duration);

            songCardsContainer.appendChild(card);
        });
    }

    function formatDuration(seconds) {
        let minutes = Math.floor(seconds / 60);
        let remainingSeconds = seconds % 60;
        return `${minutes}:${remainingSeconds.toString().padStart(2, '0')}`;
    }
});
