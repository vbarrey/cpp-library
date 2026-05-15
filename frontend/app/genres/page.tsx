import { isMediaType, fetchAllGenres, fetchGenreByMediaType, MediaType, Genre, Paginated } from "@/lib/api";
import GenreCard from "@/components/genre-card";

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

    return (
        <div>
            <h1 className="text-4xl font-bold mb-4">Genres</h1>

            <div className="grid grid-cols-3 gap-4">
                {result.data.map((genre) => (
                    <GenreCard key={genre.id} genre={genre} />
                ))}
            </div>
        </div>
    );
}