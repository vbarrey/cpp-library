import { Genre } from "@/lib/api";
import { Badge } from "@/components/ui/badge";

export function GenresList({ genres, mediaId }: { genres: Genre[], mediaId: string }) {
    return (
        <div className="flex gap-2 pt-2">
            {genres && genres.map((genre) => (
                <Badge key={`${mediaId}-${genre.id}`} variant="secondary">
                    {genre.name}
                </Badge>
            ))}
        </div>
    );
}