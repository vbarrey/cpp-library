import { isMediaType, fetchAllGenres, fetchGenreByMediaType, MediaType, Genre, Paginated } from "@/lib/api";

export default async function GenresPage({ searchParams }: { searchParams: Promise<{ mediaType?: string }> }) {
    const { mediaType } = await searchParams;

    let result: Paginated<Genre>;

    if (mediaType) {
        if (mediaType.length === 0 || !isMediaType(mediaType)) {
            throw new Error("Invalid media type");
        }

        result = await fetchGenreByMediaType(mediaType as MediaType);
    }else{
        result = await fetchAllGenres();
    }

    console.log(result);

    return (
        <div>
            <h1>Genres</h1>
            <ul>
                {result.data.map((genre) => (
                    <li key={genre.id}>{genre.name}</li>
                ))}
            </ul>
        </div>
    );
}