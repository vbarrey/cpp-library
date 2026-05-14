import { fetchBookGenre } from "@/lib/api";

export default async function GenresPage() {

    const bookGenres = await fetchBookGenre();

    return (
        <div>
            <h1>Genres</h1>
            <ul>
                {bookGenres.map((genre) => (
                    <li key={genre.id}>{genre.name}</li>
                ))}
            </ul>
        </div>
    );
}